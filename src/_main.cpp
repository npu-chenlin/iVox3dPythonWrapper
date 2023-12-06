#include "Svar.h"
#include "ivox3d.h"
// timeit
#include <chrono>
REGISTER_SVAR_MODULE(ivox3d){
    using namespace faster_lio;
    using Vox3d=IVox<3, IVoxNodeType::PHC, pcl::PointXYZ>;
    sv::Class<Vox3d::Options>("IVoxOption","Options of IVox")
        .construct<double, double, int, int>()
        .def("set_resolution",[](Vox3d::Options& self, double resolution){
            self.resolution_=resolution;
        })
        .def("set_inv_resolution",[](Vox3d::Options& self, double inv_resolution){
            self.inv_resolution_=inv_resolution;
        })
        .def("set_capacity",[](Vox3d::Options& self, double capacity){
            self.capacity_=capacity;
        });

    sv::Class<Vox3d>("IVox","A class for 3d voxelization")
        .construct<Vox3d::Options>()
        .def("NumValidGrids",&Vox3d::NumValidGrids)
        .def("GetClosestPoint",[](Vox3d& self, std::vector<double> xyz){
            pcl::PointXYZ p(xyz[0], xyz[1], xyz[2]);
            pcl::PointXYZ p_ret(0,0,0);
            self.GetClosestPoint(p, p_ret);
            return std::vector<double>{p_ret.x,p_ret.y,p_ret.z};
        })
        .def("GetClosestPoints",[](Vox3d& self, std::vector<double> xyz, int max_num, double max_range){
            pcl::PointXYZ p(xyz[0], xyz[1], xyz[2]);
            std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ>> ps_ret;
            self.GetClosestPoint(p, ps_ret, max_num, max_range);
            std::vector<double> ret;
            ret.reserve(ps_ret.size()*3);
            for(auto& p:ps_ret)
                ret.insert(ret.end(),{p.x,p.y,p.z});
            return ret;
        })
        .def("AddPoints", [](Vox3d& self, std::vector<double> points){
            double enter_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ>> ps;
            ps.reserve(points.size()/3);
            for(size_t i=0;i<points.size();i+=3)
                ps.emplace_back(points[i],points[i+1],points[i+2]);
            double transform_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            self.AddPoints(ps);
            double add_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            // std::cout<<"Add "<<points.size()/3<<" points, transform time "<<(transform_time-enter_time)/1e6<<"ms, add time "<<(add_time-transform_time)/1e6<<"ms"<<std::endl;
        });
}
EXPORT_SVAR_INSTANCE 