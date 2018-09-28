/*
 * (C) Copyright 2017-2018 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#include "ufo/atmosphere/gnssro/ObsGnssroBndGSI.h"

#include <ostream>
#include <string>
#include <vector>

#include "ioda/ObsVector.h"

#include "oops/base/Variables.h"
#include "oops/util/Logger.h"

#include "ufo/GeoVaLs.h"
#include "ufo/ObsBias.h"

namespace ufo {

// -----------------------------------------------------------------------------
static ObsOperatorMaker<ObsGnssroBndGSI> makerGnssroBndGSI_("GnssroBndGSI");
// -----------------------------------------------------------------------------

ObsGnssroBndGSI::ObsGnssroBndGSI(const ioda::ObsSpace & odb, const eckit::Configuration & config)
  : keyOperGnssroBndGSI_(0), varin_(), odb_(odb)
{
  const std::vector<std::string> vv{"temperature", "specific_humidity", "air_pressure",
                                    "air_pressure_levels", "geopotential_height_levels"};

  varin_.reset(new oops::Variables(vv));
  const eckit::Configuration * configc = &config;
  ufo_gnssro_bndgsi_setup_f90(keyOperGnssroBndGSI_, &configc);
  oops::Log::trace() << "ObsGnssroBndGSI created." << std::endl;
}

// -----------------------------------------------------------------------------

ObsGnssroBndGSI::~ObsGnssroBndGSI() {
  ufo_gnssro_bndgsi_delete_f90(keyOperGnssroBndGSI_);
  oops::Log::trace() << "ObsGnssroBndGSI destructed" << std::endl;
}

// -----------------------------------------------------------------------------

void ObsGnssroBndGSI::simulateObs(const GeoVaLs & gom, ioda::ObsVector & ovec,
                                const ObsBias & bias) const {
  ufo_gnssro_bndgsi_simobs_f90(keyOperGnssroBndGSI_, gom.toFortran(), odb_.toFortran(),
                           ovec.toFortran(), bias.toFortran());
}

// -----------------------------------------------------------------------------

void ObsGnssroBndGSI::print(std::ostream & os) const {
  os << "ObsGnssroBndGSI::print not implemented";
}

// -----------------------------------------------------------------------------

}  // namespace ufo
