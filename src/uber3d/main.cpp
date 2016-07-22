
#include "map.h"
#include "sfb_coefficients.h"
#include "sfb_transform.h"
#include "bessel_sampling.h"
#include "healpix_sampling.h"

int main (int argc, const char **argv){
    
    
    // Defines a radial and spherical sampling scheme
    double Rmax;
    long N;
    uber3d::bessel_sampling r_samp(Rmax, N);
    uber3d::healpix_sampling sph_samp(512);
    
    // Creates a new map
    uber3d::map<double> new_map(r_samp, sph_samp);
    
    // Exports new map to HDF5 file
    new_map.to_HDF5("3dmap.hdf", "map_in");
    
    // Loads a map from an HDF5 dataset
    uber3d::map<double> my_map("3dmap.hdf","map_in");
    
    // Creates a new empty set of almn coefficients
    uber3d::sfb_coefficients<double> almn;
    
    // Creates a new SFB transform
    long lmax = 100;
    long nmax = 100;
    uber3d::sfb_transform transform(my_map.get_radial_sampling(), my_map.get_spherical_sampling(), lmax, nmax);
    
    // Apply the transform
    transform.foward(my_map, almn);
    
    // Saves the computed coefficients
    almn.to_HDF5("3dmap.hdf", "almn_out");
    
}