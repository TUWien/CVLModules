
#include "MyWriterRetrieval.h"
#include "../Image.h"

#include <iostream>
#include <iomanip>

#include "WriterRetrieval.h"
#include "WriterDatabase.h"

namespace transkribus {


MyWriterRetrieval::MyWriterRetrieval() {}

MyWriterRetrieval::~MyWriterRetrieval()
{
	std::cout << "MyWriterRetrieval is deleted!" << std::endl;
}

std::string MyWriterRetrieval::process(const Image& image, const std::string& xmlIn, 
									   const std::vector<std::string>& ids,
										const std::vector<std::string>& props) {
	std::cout << "MyWriterRetrieval, process, xmlIn =  " << xmlIn << std::endl;
	std::cout << image << std::endl;

	std::string vocPath = "";
	for(int i = 0; i < ids.size(); i++) {
		
		if(ids[i].compare("vocPath") == 0)
			vocPath = props[i];
	}


	if(vocPath == "") {
		std::cout << "vocabulary path not set ... aborting";
		return "";
	}

	rdf::WriterRetrieval wr = rdf::WriterRetrieval();
	wr.setImage(image.mat());
	wr.calculateFeatures();

	rdf::WriterVocabulary wv = rdf::WriterVocabulary(); // TODO load the correct Voc
	wv.loadVocabulary(QString::fromStdString(vocPath));
	cv::Mat feature = wv.generateHist(wr.descriptors());
	
	std::stringstream featureStream;
	
	if(feature.rows == 1) { // must be a vector
		const float* f = feature.ptr<float>(0);
		for(int i = 0; i < feature.cols; i++) {
			featureStream << std::fixed << std::setprecision(10) << f[i];
			//featureStream << std::to_string(f[i]);
			if(i != feature.cols - 1)
				featureStream << ",";
		}
	}
	
	return featureStream.str();
}

Image MyWriterRetrieval::distances(const Image& features,
								   const std::vector<std::string>& ids,
								   const std::vector<std::string>& props) {

	std::string vocPath = "";
	for(int i = 0; i < ids.size(); i++) {

		if(ids[i].compare("vocPath") == 0)
			vocPath = props[i];
	}

	if(vocPath == "") {
		std::cout << "vocabulary path not set ... aborting";
		return "";
	}

	rdf::WriterVocabulary wv = rdf::WriterVocabulary(); 
	wv.loadVocabulary(QString::fromStdString(vocPath));
	cv::Mat distances = wv.calcualteDistanceMatrix(features.mat());

	Image result = Image(distances);

	return Image();
}

Image MyWriterRetrieval::train(const std::vector<Image>& features,
							   const std::vector<std::string>& ids,
							   const std::vector<std::string>& props) {
	return Image();
}


const std::string MyWriterRetrieval::usage() const {
	return std::string("MyUsage");
}

const std::string MyWriterRetrieval::getToolName() const {
	return std::string("Writer Retrieval");
}

const std::string MyWriterRetrieval::getVersion() const {
	return std::string("0.0.1");
}

const std::string MyWriterRetrieval::getProvider() const {
	return std::string("MyProvider");
}


IModule * MyWriterRetrievalModuleFactory::create(const std::vector<std::string>& pars)
{
	std::cout << "creating MyWriterRetrieval" << std::endl;
	return new MyWriterRetrieval;
}

}
