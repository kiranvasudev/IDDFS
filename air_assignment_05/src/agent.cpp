/*
 * Daniel Vazquez, Kiran Vasudev, Patrick Nagel
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 5
 *
 * agent.cpp
 * */

#include "agent.hpp"

#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <string>

#define map_rows 25
#define map_cols 141

using namespace std;

Agent::Agent(vector<vector<string> > map, const pair<int, int> initial_pos,
		int number_of_goals) :
		empty_map(map), initial_pos(initial_pos), number_of_goals(
				number_of_goals), max_number_of_stored_nodes(0), number_of_visited_nodes(
				0), total_of_stored_nodes(0), deepest_level(0) {
	max_limit = map_rows * map_cols;
}

Agent::~Agent() {
}

void Agent::run() {
	cout << "Running IDFS " << endl;
	cout << "Number of goals " << number_of_goals << endl;
	sleep(1);
	iterative_deepening_search();
}

void Agent::print_map(vector<vector<string> >& a_map) {
	system("clear");

	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			cout << a_map[row][col];
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(10));
}

bool Agent::recursive_dls(pair<int, int> current_node, int goal,
		int current_level, int limit, vector<pair<int, int> > current_path) {

//	current_path.push_back(current_node);
//	std::string goalStr = std::to_string(goal);

	int row = current_node.first;
	int column = current_node.second;

	cout << "row: " << row;
	cout << "column: " << column;
	if (map[row][column] == "1") {
		cout << "goal found" << endl;
		return true;

	} else {
		map[current_node.first][current_node.second] = "-";
	}

	if (current_level == limit) {
		return false;
	} else {
		if (map[current_node.first][current_node.second + 1] == " "
				|| map[current_node.first][current_node.second + 1]
						== "1"/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(
					make_pair(current_node.first, current_node.second + 1),
					goal, current_level, limit, current_path);
		}
		if (map[current_node.first][current_node.second - 1] == " "
				|| map[current_node.first][current_node.second - 1]
						== "1"/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(
					make_pair(current_node.first, current_node.second - 1),
					goal, current_level, limit, current_path);
		}
		if (map[current_node.first + 1][current_node.second] == " "
				|| map[current_node.first + 1][current_node.second]
						== "1"/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(
					make_pair(current_node.first + 1, current_node.second),
					goal, current_level, limit, current_path);
		}
		if (map[current_node.first - 1][current_node.second] == " "
				|| map[current_node.first - 1][current_node.second]
						== "1"/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(
					make_pair(current_node.first - 1, current_node.second),
					goal, current_level, limit, current_path);
		}
	}

	number_of_visited_nodes++;
	map[current_node.first][current_node.second] = "0";
	return true;
//TODO

//Notes:
//Backtrack from here once you have found a goal.
//If you have found a goal, do not forget to get a fresh copy of the map.
//Stop searching if you have found a goal or reached the depth limit.
//Only return true if you have found a goal.

}

bool Agent::depth_limited_seach(int limit) {
	vector<pair<int, int> > current_path;
	int goal = 1;
	while (limit != max_limit || goal != number_of_goals) {
		recursive_dls(initial_pos, goal, 0, limit, current_path);
		limit += 1;
		goal += 1;
	}
	return true;
}

void Agent::iterative_deepening_search() {
	depth_limited_seach(0);
}

void Agent::print_final_results() {
	cout << "Deepest level reached: " << deepest_level << endl;
	cout << "Total of stored nodes: " << total_of_stored_nodes << endl;
	cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
}

void Agent::backtrack_path(vector<pair<int, int> > current_path) {
	//use the original map to backtrace
	vector<vector<string> > local_map = empty_map;

	pair<int, int> current_data;

	//TODO
	//Backtrace. Use the current path vector to set the path on the map.

	//print backtraced path
	print_map(local_map);
}
