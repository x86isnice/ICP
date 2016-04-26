#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <list>
#include <ctime>
#include <pcl/registration/icp.h>

using namespace std;
using namespace pcl;

int main (int argc, char** argv)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);

	pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
       // Fill in the CloudIn data
	pcl::io::loadPCDFile("./1.pcd", *cloud_in);
	pcl::io::loadPCDFile("./2.pcd", *cloud_out);
	icp.setInputCloud(cloud_in);
	icp.setInputTarget(cloud_out);


	// Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
	icp.setMaxCorrespondenceDistance (5);
	// Set the maximum number of iterations (criterion 1)
	icp.setMaximumIterations (50000000);
	// Set the transformation epsilon (criterion 2)
	icp.setTransformationEpsilon (1e-18);
	// Set the euclidean distance difference epsilon (criterion 3)
	icp.setEuclideanFitnessEpsilon (0.001);


	// Obtain the transformation that aligned cloud_source to cloud_source_registered
	//Eigen::Matrix4f transformation = icp.getFinalTransformation ();

	pcl::PointCloud<pcl::PointXYZ> Final;
	icp.align(Final);
	
	std::cout << "has converged:" << icp.hasConverged() << " score: " <<
	icp.getFitnessScore() << std::endl;
	std::cout << icp.getFinalTransformation() << std::endl;
	pcl::io::savePCDFileASCII("./outdata.pcd",Final);
	return (0);
}

