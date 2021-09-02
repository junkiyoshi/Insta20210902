#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(39);

	this->hexagon_height = 8;
	this->hexagon_width = 4;

	for (float x = this->hexagon_width * 9; x <= ofGetWidth() - this->hexagon_width * 9; x += this->hexagon_height * 1.5) {

		for (float y = this->hexagon_height * 3; y <= ofGetHeight() - this->hexagon_height * 3; y += this->hexagon_height * 3) {

			this->number_list.push_back(make_pair(glm::vec2(x, y), 0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (auto& number : this->number_list) {

		number.second = number.second > 0 ? number.second - 0.01 : 0;
	}

	for (int i = 0; i < 1; i++) {

		int deg_start = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -360, 360);
		int radius = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -350, 350);

		for (int deg = deg_start; deg < deg_start + 360; deg += 60) {

			auto noise_location = glm::vec2(radius * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.5, radius * sin(deg * DEG_TO_RAD) + ofGetHeight() * 0.5);

			for (auto& number : this->number_list) {

				if (glm::distance(noise_location, number.first) < 15) {

					number.second = number.second < 100 ? number.second + 8 : 100;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& number : this->number_list) {

		if (number.second > 0) {

			int number_index = ofMap(ofNoise(glm::vec3(number.first * 0.05, ofGetFrameNum() * 0.03)), 0, 1, 0, 10);
			this->draw_digital(number.first, number_index);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_digital(glm::vec2 location, int number_index) {

	vector<pair<glm::vec2, float>> part_list = {
		make_pair<glm::vec2, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, 0), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	vector<vector<int>> index_list = {
		{ 0, 1, 2, 4, 5, 6 },
		{ 2, 5 },
		{ 0, 1, 3, 5, 6 },
		{ 0, 2, 3, 5, 6 },
		{ 2, 3, 4, 5 },
		{ 0, 2, 3, 4, 6 },
		{ 0, 1, 2, 3, 4, 6 },
		{ 0, 2, 5 },
		{ 0, 1, 2, 3, 4, 5, 6 },
		{ 0, 2, 3, 4, 5, 6 },
	};

	for (auto& index : index_list[number_index]) {

		this->draw_hexagon(part_list[index].first, part_list[index].second);
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec2 location, float deg) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * 0.5));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * -0.5));

	ofFill();
	ofSetColor(239);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}