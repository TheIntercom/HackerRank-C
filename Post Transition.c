/*
This prompt provides the includes, main with driver code, and the structs.

We are asked to complete the logic and operation of the following functions:
-- print_all_packages : Print the information relating to packages in a specific format.
-- send_all_acceptable_packages : Send certain packages from one town to another town in a specific order.
-- town_with_most_packages : Return the first town from a provided list that contains the most packages.
-- find_town : Return a town pointer from a provided list that matches a supplied name.

Sample input:
2
A
2
2 1 3
a 2
b 3
1 2 4
c 2
B
1
4 1 4
d 1
e 2
f 3
h 4
5
3
2 B 0 A 1
3
1 A
1 B

Sample output:
Town with the most number of packages is B
Town with the most number of packages is A
A:
    0:
        a
        b
    1:
        c
        e
        f
        h
B:
    0:
        d
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

// ------------------ code above is provide by the prompt ------------------

void print_all_packages(town t) {
    printf("%s:\n", t.name);

    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);

        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    // we want to keep the order of the packages for both post offices so
    // i think it could make sense here to just build some temp arrays and fill them
    // rather than remove, reorder, and realloc

    post_office* source_post_office = &source->offices[source_office_index];
    post_office* target_post_office = &target->offices[target_office_index];

    int package_weight;
    int target_min_weight = target_post_office->min_weight;
    int target_max_weight = target_post_office->max_weight;

    int acceptable_package_count = 0;

    // count the acceptable packages
    for (int i = 0; i < source_post_office->packages_count; i++) {
        package_weight = source_post_office->packages[i].weight;

        // if its the correct weight we want it
        if (package_weight >= target_min_weight && package_weight <= target_max_weight)
            acceptable_package_count++;
    }

    package* new_source_packages = malloc(sizeof(package) * (source_post_office->packages_count - acceptable_package_count)); // less space for fewer packages
    package* new_target_packages = malloc(sizeof(package) * (target_post_office->packages_count + acceptable_package_count)); // more space for more packages

    //initialize the new target array with the old target packages
    for (int i = 0; i < target_post_office->packages_count; i++) {
        new_target_packages[i] = target_post_office->packages[i];
    }

    int new_source_index = 0;
    int new_target_index = target_post_office->packages_count;

    // read every package from source in order, source is now "empty"
    for (int i = 0; i < source_post_office->packages_count; i++) {
        package_weight = source_post_office->packages[i].weight;

        if (package_weight >= target_min_weight && package_weight <= target_max_weight) {
            // if weight conditions are correct, add to tail of target
            new_target_packages[new_target_index] = source_post_office->packages[i];
            new_target_index++;
        } else {
            // if weight condition are wrong, add to next lowest index of source
            new_source_packages[new_source_index] = source_post_office->packages[i];
            new_source_index++;
        }
    }

    // free and replace old package arrays (and update package count)
    free(source_post_office->packages);
    source_post_office->packages = new_source_packages;
    source_post_office->packages_count = new_source_index;

    free(target_post_office->packages);
    target_post_office->packages = new_target_packages;
    target_post_office->packages_count = new_target_index;
}

town town_with_most_packages(town* towns, int towns_count) {
    int most_packages = 0;
    int town_packages = 0;
    int town_index = -1;

    for (int i = 0; i < towns_count; i++) {
        for (int j = 0; j < towns[i].offices_count; j++) {
            town_packages += towns[i].offices[j].packages_count;
        }

        if (town_packages > most_packages) {
            most_packages = town_packages;
            town_index = i;
        }

        town_packages = 0;
    }

    return towns[town_index];
}

town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (!strcmp(towns[i].name, name)) {
            return &towns[i];
        }
    }

    return &towns[0];
}

// ------------------ code below is provide by the prompt ------------------

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
