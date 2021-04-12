#ifndef __L1Trigger_L1THGCal_HGCalHistoSeedingImpl_h__
#define __L1Trigger_L1THGCal_HGCalHistoSeedingImpl_h__

#include "DataFormats/L1THGCal/interface/HGCalCluster.h"
#include "DataFormats/L1THGCal/interface/HGCalMulticluster.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerTools.h"
#include "L1Trigger/L1THGCal/interface/backend/HGCalShowerShape.h"
#include "L1Trigger/L1THGCal/interface/backend/HGCalTriggerClusterIdentificationBase.h"

#include "TH2.h"
#include "TFile.h"

class HGCalHistoSeedingImpl {
private:
  struct Bin {
    enum Content { Sum, Ecal, Hcal };
    std::array<float, 3> values = {{0., 0., 0.}};
    float weighted_x = 0.;
    float weighted_y = 0.;
  };
  template <typename T>
  class HistogramT {
  public:
    using Data = std::vector<T>;
    using iterator = typename Data::iterator;
    using const_iterator = typename Data::const_iterator;

  public:
    HistogramT() : bins1_(0), bins2_(0), bins_(0) {}
    HistogramT(unsigned bins1, unsigned bins2)
        : bins1_(bins1), bins2_(bins2), bins_(bins1 * bins2), histogram_(bins_ * kSides_) {}

    T& at(int zside, unsigned x1, unsigned x2) { return histogram_[index(zside, x1, x2)]; }

    const T& at(int zside, unsigned x1, unsigned x2) const { return histogram_[index(zside, x1, x2)]; }

    iterator begin() { return histogram_.begin(); }
    const_iterator begin() const { return histogram_.begin(); }
    iterator end() { return histogram_.end(); }
    const_iterator end() const { return histogram_.end(); }

    unsigned nbins1() {return bins1_;}
    unsigned nbins2() {return bins2_;}

  private:
    static constexpr unsigned kSides_ = 2;
    unsigned bins1_ = 0;
    unsigned bins2_ = 0;
    unsigned bins_ = 0;
    Data histogram_;

    unsigned index(int zside, unsigned x1, unsigned x2) const {
      if (x1 >= bins1_ || x2 >= bins2_) {
        throw cms::Exception("OutOfBound") << "Trying to access bin (" << x1 << "," << x2
                                           << ") in seeding histogram of size (" << bins1_ << "," << bins2_ << ")";
      }
      return x2 + bins2_ * x1 + bins_ * (zside > 0 ? 1 : 0);
    }
  };
  using Histogram = HistogramT<Bin>;

  void SaveHistoAs(Histogram hist, const char* filename, float xmin=0, float xmax=-1, float ymin=0, float ymax=-1) {
     TFile f(filename, "RECREATE");
     f.cd();
     unsigned nbins1 = hist.nbins1();
     unsigned nbins2 = hist.nbins2();
     if (xmax<xmin) {xmin=0; xmax=nbins1;}
     if (ymax<ymin) {ymin=0; ymax=nbins2;}
     TH2F hplusS("hplusS", "+z side (Sum);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     TH2F hminusS("hminusS", "-z side (Sum);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     TH2F hplusE("hplusE", "+z side (Ecal);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     TH2F hminusE("hminusE", "-z side (Ecal);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     TH2F hplusH("hplusH", "+z side (Hcal);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     TH2F hminusH("hminusH", "-z side (Hcal);r;#phi", nbins1, xmin, xmax, nbins2, ymin, ymax);
     for (unsigned i=0; i<nbins1; i++)
        for (unsigned j=0; j<nbins2; j++) {
           hplusS.SetBinContent(i+1, j+1, hist.at(1, i, j).values[Bin::Content::Sum]);
           hminusS.SetBinContent(i+1, j+1, hist.at(-1, i, j).values[Bin::Content::Sum]);
           hplusE.SetBinContent(i+1, j+1, hist.at(1, i, j).values[Bin::Content::Ecal]);
           hminusE.SetBinContent(i+1, j+1, hist.at(-1, i, j).values[Bin::Content::Ecal]);
           hplusH.SetBinContent(i+1, j+1, hist.at(1, i, j).values[Bin::Content::Hcal]);
           hminusH.SetBinContent(i+1, j+1, hist.at(-1, i, j).values[Bin::Content::Hcal]);
        }
     hplusS.Write("hplusS");
     hminusS.Write("hminusS");
     hplusE.Write("hplusE");
     hminusE.Write("hminusE");
     hplusH.Write("hplusH");
     hminusH.Write("hminusH");
     f.Close();
  }

  class Navigator {
  public:
    enum class AxisType { Bounded, Circular };

    Navigator() : axis_types_({{AxisType::Bounded, AxisType::Bounded}}), bins_({{0, 0}}), home_({{0, 0}}) {}

    Navigator(int bins1, AxisType type_axis1, int bins2, AxisType type_axis2)
        : axis_types_({{type_axis1, type_axis2}}), bins_({{bins1, bins2}}), home_({{0, 0}}) {}

    void setHome(int x1, int x2) {
      if (x1 < 0 || x2 < 0 || x1 >= std::get<0>(bins_) || x2 >= std::get<1>(bins_)) {
        throw cms::Exception("OutOfBound") << "Setting invalid navigator home position (" << x1 << "," << x2 << "\n)";
      }
      home_[0] = x1;
      home_[1] = x2;
    }

    std::array<int, 2> move(int offset1, int offset2) { return {{offset<0>(offset1), offset<1>(offset2)}}; }

    template <unsigned N>
    int offset(int shift) {
      int shifted = std::get<N>(home_);
      int max = std::get<N>(bins_);
      switch (std::get<N>(axis_types_)) {
        case AxisType::Bounded:
          shifted += shift;
          if (shifted < 0 || shifted >= max)
            shifted = -1;
          break;
        case AxisType::Circular:
          shifted += shift;
          while (shifted < 0)
            shifted += max;
          while (shifted >= max)
            shifted -= max;
          break;
        default:
          break;
      }
      return shifted;
    }

  private:
    std::array<AxisType, 2> axis_types_;
    std::array<int, 2> bins_;
    std::array<int, 2> home_;
  };

public:
  HGCalHistoSeedingImpl(const edm::ParameterSet& conf);

  void eventSetup(const edm::EventSetup& es) { triggerTools_.eventSetup(es); }

  float dR(const l1t::HGCalCluster& clu, const GlobalPoint& seed) const;

  void findHistoSeeds(const std::vector<edm::Ptr<l1t::HGCalCluster>>& clustersPtr,
                      std::vector<std::pair<GlobalPoint, double>>& seedPositionsEnergy);

private:
  enum SeedingType { HistoMaxC3d, HistoSecondaryMaxC3d, HistoThresholdC3d, HistoInterpolatedMaxC3d };
  enum SeedingSpace { RPhi, XY };
  enum SeedingPosition { BinCentre, TCWeighted };

  Histogram fillHistoClusters(const std::vector<edm::Ptr<l1t::HGCalCluster>>& clustersPtrs);

  Histogram fillSmoothHistoClusters(const Histogram&, const vector<double>&, Bin::Content);
  Histogram fillSmoothPhiHistoClusters(const Histogram& histoClusters, const vector<unsigned>& binSums);
  Histogram fillSmoothRPhiHistoClusters(const Histogram& histoClusters);

  void setSeedEnergyAndPosition(std::vector<std::pair<GlobalPoint, double>>& seedPositionsEnergy,
                                int z_side,
                                unsigned bin_R,
                                unsigned bin_phi,
                                const Bin& histBin);

  std::vector<std::pair<GlobalPoint, double>> computeMaxSeeds(const Histogram& histoClusters);

  std::vector<std::pair<GlobalPoint, double>> computeSecondaryMaxSeeds(const Histogram& histoClusters);

  std::vector<std::pair<GlobalPoint, double>> computeInterpolatedMaxSeeds(const Histogram& histoClusters);

  std::vector<std::pair<GlobalPoint, double>> computeThresholdSeeds(const Histogram& histoClusters);

  std::array<double, 4> boundaries();

  std::array<float, 3> findMax(Histogram hist);
  std::array<float, 3> findMaxPt(Histogram hist);

  std::string seedingAlgoType_;
  SeedingType seedingType_;
  SeedingSpace seedingSpace_;
  SeedingPosition seedingPosition_;

  unsigned nBins1_ = 42;
  unsigned nBins2_ = 216;
  std::vector<unsigned> binsSumsHisto_;
  double histoThreshold_ = 20.;
  static constexpr double area_per_triggercell_ =
      4.91E-05;  // Hex_Wafer_Area (x/z units)/N_TC (per wafer) = (0.866*((hexWafer_minimal_diameter)*(1./319.))^2 / 48)
  std::vector<double> neighbour_weights_;
  std::vector<double> smoothing_ecal_;
  std::vector<double> smoothing_hcal_;

  HGCalTriggerTools triggerTools_;
  Navigator navigator_;

  static constexpr unsigned neighbour_weights_size_ = 9;
  const double kROverZMin_ = 0.076;
  const double kROverZMax_ = 0.58;

  static constexpr double kXYMax_ = 0.6;
};

#endif

