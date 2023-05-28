# Nearest-Neighbors-Search / Multi-Dimensional-Data-Clustering
This project implements two fundamental algorithmic aspects for multi dimensional data handling.
* implements state of the art approximation algorithms for exact nearest neighbors search on multi-dimensional vectors.
* implements clustering algorithms on multi-dimensional data.

## Nearest-Neighbors-Search Algorithms Implemented:
* Locality Sensitive Hashing (LSH)
* Random Projection on multi-dimensional Hypercube

## Clustering Algorithms Implemented:
The implemented clustering algorithms follow the general principle of centroid-based clustering. The clusters are defined by a set of centroids, each multi-dimensional vector is assigned to its (exact or approximate) closest centroid. So the clustering problem is reduced to the initialization and iterative improvement of the centroids, with respect to the input vectors. Various approaches are implemented:
### Centroid Initialization:
* k-means++ initialization technique
### Vector to Centroid Assignment:
* Lloyd's exact nearest centroid algorithm
* Range search for approximate nearest centroid (using LSH or Hypercube random projection algorithms)

### Update:
* Mean Vector method

The Silhouette metric is used for the evaluation of the quality of the clustering.

**The project was developed as part of the "Software Development for Hard Algorithmic Problems" course of the Computer Science Department of the university of Athens (NKUA)**
