#ifndef VMAPPING_INCLUDE_VMAPPING_H
#define VMAPPING_INCLUDE_VMAPPING_H

#include <Eigen/Core>
#include <memory>
#include <opencv2/opencv.hpp>

namespace vmap
{
class VoxelMapping
{
public:
    VoxelMapping(int w, int h, const Eigen::Matrix3f& K);
    ~VoxelMapping();

    void reset();
    void CreateMap(int numEntries, int numVoxels, float voxelSize);
    void FuseDepth(cv::cuda::GpuMat depth, const Eigen::Matrix4f& camToWorld);
    void FuseDepthAndImage(cv::Mat rgb, cv::Mat depth, const Eigen::Matrix4f& camToWorld);
    void RenderScene(cv::cuda::GpuMat& vmap, const Eigen::Matrix4f& camToWorld);
    int Polygonize(float*& verts_out, float*& norms_out);
    std::vector<Eigen::Vector3f> GetSurfacePoints();

protected:
    struct VoxelizationImpl;
    std::unique_ptr<VoxelizationImpl> impl;
};

} // namespace vmap

#endif