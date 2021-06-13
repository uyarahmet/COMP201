/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lookup_string(char str[30]); // added prototype, it was causing implicit call warning. 

const int INF = 1e7;

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (*str)[30];
} vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (*edge)[3];
} edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()
{
	for (int k = 0; k < cities.city_count; k++)
	{
		for (int i = 0; i < cities.city_count; i++)
		{
			for (int j = 0; j < cities.city_count; j++)
			{

				// We cannot cross a road that doesn't exist
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))
				{
					continue;
				}

				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j]))
				{
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];
					shortest_paths[i][j] = shortest_paths[i][k];
				}
			}
		}
	}
}

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()
{
	for (int i = 0; i < cities.city_count; i++)
	{
		for (int j = 0; j < cities.city_count; j++)
		{

			// No edge between node i and j
			if (city_graph[i][j] == INF)
			{
				shortest_paths[i][j] = -1;
			}
			else
			{
				shortest_paths[i][j] = j;
			}
		}
	}
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int insert_to_cities(char str[30])
{

	// Write your code here
	// Check if the city name already exists in the array
	// If it does, return the array index of the city
	
	if (lookup_string(str) != -1)
	{

		return lookup_string(str);
	}

	// If the city name doesn't exist, it is inserted to the cities array, and
	// return the array index of the city
	// If the dynamically allocated size of cities array is not large enough,
	// the size of cities array is enlarged and the city name is inserted
	// to the newly added region
	// Return the array index of the city.

	size_t new_size = (cities.city_count + 1) * sizeof(char[30]);
	if (new_size > cities.size)
	{
		cities.str = realloc(cities.str, new_size);
		cities.size = new_size;
	}

	strcpy(cities.str[cities.city_count], str);
	return cities.city_count++;
}

/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30])
{
	for (int i = 0; i < cities.city_count; i++)
	{
		if (strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	return -1;
}

void printPath(int u, int v)
{
	// Write your code here

	if (shortest_paths[u][v] == -1) // -1 if no path 
	{
		printf("*** NO PATH ***\n");
		return;
	}

	int sum = 0;
	char *output_line = malloc(sizeof(char) * 100); // output must be open to addition 
	char *space = " "; // couldn't find a better way.

	while (shortest_paths[u][v] != v) // until destination is reached
	{
		sum += city_graph[u][shortest_paths[u][v]]; // sum up the road lengths
		strcat(output_line, cities.str[u]); // creating output stream
		strcat(output_line, space);
		u = shortest_paths[u][v]; // setting new destination
	}
	sum += city_graph[u][v]; // adding last road. (or first)

	strcat(output_line, cities.str[u]);
	strcat(output_line, space);
	strcat(output_line, cities.str[v]);

	printf("%s\n%d\n\n", output_line, sum);
	free(output_line); // freeing output line. 
}

int main(int argc, char *argv[])
{
	// Write your code here
	// Allocate memory regions dynamically to cities array
	// and roads array.

	cities.size = sizeof(char[30]) * 3;
	cities.str = malloc(cities.size);
	cities.city_count = 0;

	roads.size = sizeof(int[3]) * 3;
	roads.edge = malloc(roads.size);
	roads.edge_count = 0;

	// Read and parse the input file. Insert the city names to cities array.
	// The index of the city name in the cities array becomes the city id.
	// Insert city ids and road lengths to roads array.

	if(argc != 2){
		printf("You can only enter one file! exiting. \n");
		free(cities.str);
		free(roads.edge);
		return 1;
	}

	FILE *file;
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		printf("No such file! \n");
		free(cities.str);
		free(roads.edge);
		return 1;
	}

	char *buffer = malloc(sizeof(char) * 30); // creating dynamic buffer 
	while (fgets(buffer, 30, file) != NULL)
	{
		if (buffer[0] == '\n') 
		{
			break;
		}
		char *city1 = strtok(buffer, " "); // id1
		char *city2 = strtok(NULL, " "); // id2
		char *clen = strtok(NULL, " "); // length
		int len = atoi(clen);
		insert_to_cities(city1);
		insert_to_cities(city2);

		// now inserting to roads
		int new_road_size = (roads.edge_count + 1) * sizeof(int[3]);
		if (new_road_size > roads.size)
		{
			roads.edge = realloc(roads.edge, new_road_size);
			roads.size = new_road_size;
		}
		// setting the tuples (id1, id2, len) in roads array. 
		roads.edge[roads.edge_count][0] = lookup_string(city1);
		roads.edge[roads.edge_count][1] = lookup_string(city2);
		roads.edge[roads.edge_count][2] = len;

		roads.edge_count++;
	}
	free(buffer); // freeing dynamic buffer 

	/* Allocating space for city_graph */
	city_graph = malloc(cities.city_count * sizeof(int *));
	for (int i = 0; i < cities.city_count; i++)
	{
		city_graph[i] = (int *)malloc(cities.city_count * sizeof(int));
	}

	// Initialize the values in city_graph array with road lengths,
	// such that the value in city_graph[i][j] is the road length
	// between cities i and j if these cities are directly connected
	// by a road
	// For cities m and n that are not connected directly by a road,
	// the value in city_graph[m][n] will be INF,
	// which is a large value like 10M,
	// that is assumed to be infinite.

	/* Initializing every element to INF */
	for (int i = 0; i < cities.city_count; i++)
	{
		for (int j = 0; j < cities.city_count; j++)
		{
			city_graph[i][j] = INF;
		}
	}

	/* Setting corresponding values according to roads edge count */
	for (int i = 0; i < roads.edge_count; i++)
	{
		int id1 = roads.edge[i][0];
		int id2 = roads.edge[i][1];
		int length = roads.edge[i][2];
		city_graph[id1][id2] = length;
		city_graph[id2][id1] = length; // converse is also valid. (city2 is also linked directly to city1)
	}


	// allocating memory for shortest paths array. 
	shortest_paths = malloc(cities.city_count * sizeof(int *));
	for (int i = 0; i < cities.city_count; i++)
	{
		shortest_paths[i] = (int *)malloc(cities.city_count * sizeof(int));
	}

	// input arrays are ready for initialise() and floydWarshall() to function.
	
	initialise();
	floydWarshall();

	while (1)
	{
		// prompt user to enter two city names
		// print the shortest path between the two cities
		// print the length of the path

		char *citiesbuf = malloc(50 * sizeof(char));
		printf("Enter the cities: ");
		fgets(citiesbuf, 50, stdin);
		citiesbuf[strlen(citiesbuf) - 1] = '\0'; // deleting \n

		char *city1 = strtok(citiesbuf, " ");
		char *city2 = strtok(NULL, " ");

		if ((lookup_string(city1) == -1) || (lookup_string(city2) == -1))
		{ // checking if user entered valid city name.
			printf("Invalid city names.");
			free(citiesbuf);
			break;
		}

		int shortest_distance = 0;
		char *shortest_path_names = malloc(100 * sizeof(char *));

		int id1 = lookup_string(city1);
		int id2 = lookup_string(city2);

		printPath(id1, id2);
		free(citiesbuf);
	}

	/* freeing everything and closing. */

	fclose(file);
	free(cities.str);
	free(roads.edge);
	for (int i = 0; i < cities.city_count; i++)
	{
		free(city_graph[i]);
	}
	free(city_graph);
	for (int i = 0; i < cities.city_count; i++)
	{
		free(shortest_paths[i]);
	}
	free(shortest_paths);

	return 0;
}