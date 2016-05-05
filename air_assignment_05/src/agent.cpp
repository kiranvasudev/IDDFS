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
	cout << "current level " << current_level << endl;

	// push the current node to the path
	current_path.push_back(current_node);

	// convert current goal-int in string to make it comparable with the current field value
	std::string goalStr = std::to_string(goal);

	// get the row and the column of the current node
	int row = current_node.first;
	int column = current_node.second;

	// if the current node is a goal node then call function backtrack_path (print path) and return true...
	if (map[row][column] == goalStr) {
		backtrack_path(current_path);
		return true;

		// ...otherwise mark the field. NOTE FOR MYSELF: is this necessary?
	} else {
		map[row][column] = "-";
	}

	// if the level-limit is reached then return false...
	if (current_level == limit) {
		return false;

		// ...otherwise check the children nodes
	} else {
		// .. check the right child by calling the method with the child node and an increased level
		if (map[row][column + 1] == " "
				|| map[row][column + 1]
						== goalStr/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(make_pair(row, column + 1), goal, current_level + 1,
					limit, current_path);
		}

		// .. check the left child by calling the method with the child node and an increased level
		if (map[row][column - 1] == " "
				|| map[row][column - 1]
						== goalStr/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(make_pair(row, column - 1), goal, current_level + 1,
					limit, current_path);
		}

		// .. check the up child by calling the method with the child node and an increased level
		if (map[row + 1][column] == " "
				|| map[row + 1][column]
						== goalStr/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(make_pair(row + 1, column), goal, current_level + 1,
					limit, current_path);
		}

		// ... check the down child by calling the method with the child node and an increased level
		if (map[row - 1][column] == " "
				|| map[row - 1][column]
						== goalStr/*should compare with the current goal 'goalStr'*/) {
			recursive_dls(make_pair(row - 1, column), goal, current_level + 1,
					limit, current_path);
		}
	}

	// NOTE FOR MYSELF: this part will be never reached ! (?)
	backtrack_path(current_path);
	number_of_visited_nodes++;
	map[current_node.first][current_node.second] = "0";

//TODO

//Notes:
//Backtrack from here once you have found a goal.
//If you have found a goal, do not forget to get a fresh copy of the map.
//Stop searching if you have found a goal or reached the depth limit.
//Only return true if you have found a goal.

}

bool Agent::depth_limited_seach(int limit) {
	// start with the first goal, number 1
	int goal = 1;

	// run through the map until all goals are found or the limit reaches the max_limit
	while (limit != max_limit and goal != number_of_goals) {

		// make a (new) path for every iteration
		vector<pair<int, int> > current_path;

		// get a copy of an empty_map
		map = empty_map;

		// run through the map starting at the initial pos and a level 0.
		/*NOTE FOR MYSELF: The goal will changed for every iteration.
		 * It will never find a goal and stop after max 9 iteration <-- that's wrong and need to be changed.*/
		recursive_dls(initial_pos, goal, 0, limit, current_path);

		// increase the limit with every run. NOTE FOR MYSELF: Should be the whole map check for every goal, or in total?
		limit += 1;

		// increas the goal. That's not correct and need to be changed. Look at the previous notes
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

	cout << "path: " << endl;
	for (unsigned i = 0; i < current_path.size(); ++i) {
//		cout << current_path[i].first << ", " << current_path[i].second << endl;
		current_data = current_path[i];
		local_map[current_data.first][current_data.second] = "-";
	}

	//TODO
	//Backtrace. Use the current path vector to set the path on the map.

	//print backtraced path
	print_map(local_map);
}
