#include "boruvka.h"

int main() {
	FILE * pFile;
	//read number of runs form file.
	//TODO:add a check if file exists or not
	pFile = fopen("Cases.txt", "r");
	fscanf(pFile, "%d", &number_of_runs);

	//run
	for (int i = 0; i < number_of_runs; i++)
	{
		printf("Graph %d", i);
		printf("\n-------------------------------------------------------\n");
		initGraph(pFile);

		printf("Original graph:\n");
		printData(head);

		printf("\nMST ");
		boruvkaMst();
		printData(mstTree);
		printf("\n-------------------------------------------------------\n");
	}
	return 0;
}