//
// Created by hossein on 12/2/17.
//

#include "DBscan.h"
node_t * DBscan::create_node( int index){
    auto *n = (node_t *) calloc(1, sizeof(node_t));
    if (n == nullptr)
        perror("Failed to allocate node.");
    else {
        n->index = index;
        n->next = nullptr;
    }
    return n;
}
int DBscan::append_at_end( int index, epsilon_neighbours_t *en) {
    node_t *n = create_node(index);
    if (n == nullptr) {
        free(en);
        return FAILURE;
    }
    if (en->head == nullptr) {
        en->head = n;
        en->tail = n;
    } else {
        en->tail->next = n;
        en->tail = n;
    }
    ++(en->num_members);
    return SUCCESS;
}
epsilon_neighbours_t *
    DBscan::get_epsilon_neighbours( int index, vector<Pulse>&points) {
    auto *en = (epsilon_neighbours_t *)
            calloc(1, sizeof(epsilon_neighbours_t));
    if (en == nullptr) {
        perror("Failed to allocate epsilon neighbours.");
        return en;
    }
    for (int i = 0; i < points.size(); ++i) {
        if (i == index)
            continue;
        if (Pulse::euclidean_dist(&points[index], &points[i]) <= epsilon)
            if (append_at_end(static_cast< int>(i), en) == FAILURE) {
                destroy_epsilon_neighbours(en);
                en = nullptr;
                break;
            }
    }
    return en;
}

//void DBscan::print_epsilon_neighbours(point *pulses, epsilon_neighbours_t *en) {
//    if (en) {
//        node_t *h = en->head;
//        while (h) {
//            printf("(%dm, %d, %d)\n",
//                   pulses[h->index].x,
//                   pulses[h->index].y,
//                   pulses[h->index].z);
//            h = h->next;
//        }
//    }
//}

void DBscan::destroy_epsilon_neighbours(epsilon_neighbours_t *en) {
        node_t *t, *h = en->head;
        while (h) {
            t = h->next;
            free(h);
            h = t;
        }
        free(en);
    }

int DBscan::expand( int index,  int cluster_id,vector<Pulse>&points) {
    int return_value = NOT_CORE_POINT;
    epsilon_neighbours_t *seeds =
            get_epsilon_neighbours(index, points);
    if (seeds == nullptr)
        return FAILURE;
    if (seeds->num_members < minpts)
        points[index].cluster_id = NOISE;
    else {
        points[index].cluster_id = cluster_id;
        node_t *h = seeds->head;
        while (h) {
            points[h->index].cluster_id = cluster_id;
            h = h->next;
        }
        h = seeds->head;
        while (h) {
            spread(h->index, seeds, cluster_id, points);
            h = h->next;
        }
        return_value = CORE_POINT;
    }
    destroy_epsilon_neighbours(seeds);
    return return_value;
}

int DBscan::spread( int index, epsilon_neighbours_t *seeds,  int cluster_id, vector<Pulse>&points) {
    epsilon_neighbours_t *spread =
            get_epsilon_neighbours(index, points);
    if (spread == nullptr)
        return FAILURE;
    if (spread->num_members >= minpts) {
        node_t *n = spread->head;
        Pulse *d;
        while (n) {
            d = &points[n->index];
            if (d->cluster_id == NOISE ||
                d->cluster_id == UNCLASSIFIED) {
                if (d->cluster_id == UNCLASSIFIED) {
                    if (append_at_end(n->index, seeds)
                        == FAILURE) {
                        destroy_epsilon_neighbours(spread);
                        return FAILURE;
                    }
                }
                d->cluster_id = cluster_id;
            }
            n = n->next;
        }
    }

    destroy_epsilon_neighbours(spread);
    return SUCCESS;
}

DBscan::DBscan() = default;


void DBscan::runDBScan(vector<Pulse> &points) {
    int i, cluster_id = 0;
    int order=0;
    for (i = 0; i < points.size(); ++i) {
        if (points.at(i).cluster_id == UNCLASSIFIED) {
//            cout<<++order<<endl;
            if (expand(i, cluster_id, points) == CORE_POINT)
                ++cluster_id;
        }
    }
}





