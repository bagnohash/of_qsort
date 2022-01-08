#include "ofApp.h"
#include <future>
#include <random>
#include <thread>
#include <chrono>
#include <fstream>

std::vector<int> arr;
std::vector<ofColor> colors;

std::random_device rdev;
std::mt19937 rng(rdev());
std::uniform_int_distribution<int> random(1, 401);

int ELEMENTS = 800;
int SCALE = 1;
int DELAY = 3;

bool finished = false;

void draw_array(std::vector<int>*, std::vector<ofColor>*);
void swap_indices(std::vector<int>*, int, int);
void quick_sort(std::vector<int>*, int, int, std::vector<ofColor>*);

int partition_array(std::vector<int>*, int, int, std::vector<ofColor>*);

std::thread qs;

void print(std::vector<int> v)
{
	for (auto el : v) std::cout << el << ", ";
}

void ofApp::setup(){

	std::ifstream input("data.txt");
	if (input)
	{
		input >> ELEMENTS;
		input >> DELAY;
	}

	for (int i = 0; i < ELEMENTS; i++)
	{
		arr.push_back(random(rng));
		colors.push_back(ofColor(255));
	}

	qs = std::thread(&quick_sort, &arr, 0, arr.size(), &colors);
	
	SCALE = ofGetWidth() / ELEMENTS;
}

//--------------------------------------------------------------
void ofApp::draw(){
	draw_array(&arr, &colors);
	std::cout << finished << '\n';
	std::cout << qs.joinable();
}


void draw_array(std::vector<int>* arr, std::vector<ofColor>* colors)
{
	for (int i = 0; i < arr->size(); i++)
	{
		ofSetColor(colors->operator[](i));
		ofDrawRectangle(i * SCALE, 400 - arr->operator[](i), SCALE, arr->operator[](i));
	}
}

int partition_array(std::vector<int>* arr, int start, int end, std::vector<ofColor>* colors)
{
	for (int i = start; i < end - 1; i++)
	{
		colors->operator[](i) = ofColor(69, 21, 37);
	}

	int pivot = arr->operator[](end - 1);
	int index = start;

	for (int i = start; i < end - 1; i++)
	{
		if (arr->operator[](i) < pivot)
		{
			swap_indices(arr, i, index);
			index++;
		}
	}

	for (int i = start; i < end - 1; i++)
	{
		colors->operator[](i) = ofColor::white;
	}

	swap_indices(arr, index, end - 1);
	return index;
}

void swap_indices(std::vector<int>* arr, int first, int last)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	int temp = arr->operator[](first);
	arr->operator[](first) = arr->operator[](last);
	arr->operator[](last) = temp;

}

void quick_sort(std::vector<int>* arr, int start, int end, std::vector<ofColor>* colors)
{
	std::cout << "start\n";
	if (start >= end) {
		finished = true;
		return;
	}

	int index = partition_array(arr, start, end, colors);

	quick_sort(arr, start, index, colors);
	quick_sort(arr, index + 1, end, colors);
}


void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
