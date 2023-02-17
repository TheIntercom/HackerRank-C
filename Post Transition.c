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


/*
given the town 't', print all packages in this town. They should be printed as follows:
Town_name:
    0:
        id_0
        id_1
        ...
    1:
        id_2
        id_3
        ...
    ...
where 0, 1, etc are the numbers of post offices and id_0, id_1, ... are the ids of packages from the 0th post office in the order of its queue, id_2, id_3 are from the 1st one etc. There should be one '\t' symbol before post office numbers and two '\t' symbols before the ids.
*/
void print_all_packages(town t) {
    printf("%s:\n", t.name);

    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);

        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

// given the towns 'source' and 'target' and post office indices 'source_office_index' and 'target_office_index', manage the transaction described above between the post office #'source_office_index' in town 'source' and the post office #'target_office_index' in town 'target'.
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    // we want to keep the order of the packages for both post offices so
    // i think it could make sense to just build some temp arrays and fill them
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

    /*
    "[T]he first one sends all its packages to the second one.
    The second one accepts the packages that satisfy the weight condition for the second office and rejects all other ones.
    These rejected packages return to the first office back and are stored in the same order they were stored before they were sent
    The accepted packages move to the tail of the second office's queue in the same order they were stored in the first office."

    -- read every package from source in order, source is now "empty"
    -- if weight conditions are correct, add to tail of target
    -- if weight condition are wrong, add to next lowest index of source
    */

    int new_source_index = 0;
    int new_target_index = target_post_office->packages_count;

    for (int i = 0; i < source_post_office->packages_count; i++) {
        package_weight = source_post_office->packages[i].weight;

        if (package_weight >= target_min_weight && package_weight <= target_max_weight) {
            new_target_packages[new_target_index] = source_post_office->packages[i];
            new_target_index++;
        } else {
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

// given all towns, find the one with the most number of packages in all post offices altogether. If there are several of them, find the first one from the collection 'towns'.
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

// given all towns and a string 'name', find the town with the name 'name'. It's guaranteed that the town exists.
town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (!strcmp(towns[i].name, name)) {
            return &towns[i];
        }
    }

    return &towns[0];
}

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
