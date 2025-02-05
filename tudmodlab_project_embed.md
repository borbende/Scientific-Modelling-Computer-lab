# Which embedding to choose for data extraction from Whole Slide Images? Does it even matter?

## 1. Short description

Whole Slide Imaging is one of the primary techniques that allows the creation of large pathological datasets. A whole slide image (WSI) usually contains a tissue sample that was prepared using various pathological staining and drying procedures. 
To view such an image there exists a good number of tools such as the softwares SlideViewer and QuPath which offer tools to for example, annotate on the slides. 
However, when it comes to performing analysis on a great amount of images extracted from WSIs, it is generally a better idea to utilise programming packages like openslide-python.

<picture>
<img src="https://github.com/borbende/Scientific-Modelling-Computer-lab/blob/main/wsi_p.png">
</picture>

Many machine learning models contain the conversion from image to vector data as a way to compress and highlight the most important information that is then used to perform prediction, classification, etc. Concerning neural networks, 
usually the model yields these "embeddings" right before they are pushed through something like a classification layer, making the task being performed on sequential (1D) instead of image (2D) data. There are a great many options to choose from regarding embedding generation with the goal of image classification. 
Examples: any convolutional network, pretrained models like ResNet50, Vision Transformeres, etc. (In truth, even methods like putting the tissue under a microscope and measuring infrared spectra from its surface counts as generating embeddings.)

One may ask the question: Does it matter what method/model we generate the embedding vectors with? Would it influence the quality of the classification results? The goal of this project is to explore this question on a certain level. More often than not when someone conducts a machine learning task,
they will simply look at a state of the art model and tune it to their needs. However, in this case we will go deeper and check how the embedding itself and not just something like the learning rate influences the outcome.


- Unsupervised classification models: Principal Component Analysis (PCA), Linear Discriminant Analysis (LDA), t-Disctributed Stochastic Neighbour Embedding (tSNE), Uniform Manifold Approximation and Projection (UMAP)



In order to obtain the embedding vectors and analyse them before using them to make predictions, one should simply remove the last layers of the network.
