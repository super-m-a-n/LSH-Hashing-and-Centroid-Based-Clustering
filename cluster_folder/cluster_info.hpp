//file:cluster_info.hpp//
#ifndef _CLUSTER_INFO_HPP_
#define _CLUSTER_INFO_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "object.hpp"
#include "dataset.hpp"

// class Cluster_info holds info for clustering
// i.e. the centroids and the clusters

class Cluster_info
{
private:
	std::vector <Object*> centroids;				// a vector of centroids
	std::vector <std::vector <const Object*> > clusters; 	// a vector of vectors, i.e a vector of clusters
	

public:
	Cluster_info();
	~Cluster_info();

	// executes clustering using given metric function (pointer to function) and assignment method
	// and outputs results and execution times in output file
	bool execute(const Dataset & dataset, const std::string & output_file, const std::string & method, bool complete, double (*metric)(const Object &, const Object &));
	
	// uses the dataset given, to run K-means++ initialization and find K initial centroids
	void K_means_init(const Dataset & dataset, double (*metric)(const Object &, const Object &));

	// clustering using exact lloyd's as assignment method
	void exact_lloyds(const Dataset & dataset, double (*metric)(const Object &, const Object &));
	// clustering using lsh range search as assignment method
	void lsh_range_search_clustering(const Dataset & dataset, double (*metric)(const Object &, const Object &));
	// clustering using hypercube range search as assignment method
	void cube_range_search_clustering(const Dataset & dataset, double (*metric)(const Object &, const Object &));
	
	// updates each centroid to the mean vector of its cluster, and returns true if centroids changed by little (algorithm has converged)
	bool update(double (*metric)(const Object &, const Object &));
	
	// finds silhouette for each cluster, and for clustering in total
	std::vector <double> silhouette(double (*metric)(const Object &, const Object &)) const;
	
	
};

int binary_search(const std::vector <float> & P, float x, int lower_index, int upper_index);
#endif