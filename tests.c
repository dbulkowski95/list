#include "list.h"

#include <criterion/criterion.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static listS* listInit(void)
{
	listS* list1 = (listS*)malloc(sizeof(listS));
	list1->head_p = NULL;

	return list1;
}

static listS* createTestList(const uint32_t numberOfNodes)
{
	listS* testList = listInit();
	for(size_t i = 0; i < numberOfNodes; i++)
	{
		push_back(testList, i);
	}
	return testList;
}

Test(test, noListClearTest)
{
	listS* testList = (listS*)malloc(sizeof(listS*));
	list_clear(testList);
	cr_expect(testList->head_p == NULL);
	free(testList);
	testList = NULL;
}

Test(test, pushBackTest) /*leak caused by inability of usage clear function*/
{
	const int testValue = 1;
	listS* testList = (listS*)malloc(sizeof(listS*));
	testList->head_p = NULL;
	push_back(testList, testValue);
	cr_expect(testList->head_p->value == testValue);
	free(testList);
}

Test(test, listClearTest)
{
	unsigned int optimalNumberOfIterations = 3;

	for (size_t i = 1; i < optimalNumberOfIterations + 1; i++)
	{
		listS* testList = createTestList(i);
		cr_expect(!list_clear(testList));
		testList = NULL;
	}
}

Test(test, popFirstTest)
{
	listS* testList = createTestList(3);
	int testValue = testList->head_p->next_p->value;
	cr_expect(pop_first(testList, NULL) == 0);
	cr_expect(testList->head_p->value == testValue);

	list_clear(testList);
	free(testList);
	testList = NULL;
}
