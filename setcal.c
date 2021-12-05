#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    int id;
    int cardinality;
    char **items;
} Set;
typedef struct {
    int length;
    Set **sets;
} SetArray;
typedef struct {
    char *first;
    char *second;
} RelationPair;
typedef struct {
    int id;
    int cardinality;
    RelationPair **items;
} Relation;
typedef struct {
    int length;
    Relation **relations;
} RelationArray;

Set *setCreator() {
    Set *set = malloc(sizeof(Set));
    set->id = 0;
    set->cardinality = 0;
    set->items = NULL;
    return set;
}

Relation *relCreator() {
    Relation *rel = malloc(sizeof(Relation));
    rel->items = NULL;
    rel->cardinality = 0;
    rel->id = 0;
    return rel;
}

RelationPair *relPairCreator() {
    RelationPair *relPair = malloc(sizeof(Relation));
    relPair->first = NULL;
    relPair->second = NULL;
    return relPair;
}
void setDestructor(Set *set) {
    free(set->items);
    free(set);
    //if(set != NULL) exit(EXIT_FAILURE);
}
void relPairDestructor(RelationPair *relationPair){
    free(relationPair->first);
    free(relationPair->second);
    free(relationPair);
    //if(relationPair != NULL) exit(EXIT_FAILURE);
}
void relDestructor(Relation *relation){
    free(relation->items);
    free(relation);
    //if(relation != NULL) exit(EXIT_FAILURE);
}


void setIncrement(Set *set, char *item) {
    ++(set->cardinality);
    set->items = realloc(set->items, (set->cardinality) * sizeof(char *));
    if (set->items == NULL)
        exit(EXIT_FAILURE);
    *(set->items + (set->cardinality - 1)) = item;
}

void relIncrement(Relation *rel, RelationPair *tmpRelPair) {
    ++(rel->cardinality);
    rel->items = realloc(rel->items, (rel->cardinality) * sizeof(char *));
    if (rel->items == NULL)
        exit(EXIT_FAILURE);
    *(rel->items + (rel->cardinality - 1)) = tmpRelPair;
}

void isReflexive(Relation *relation, Set *universum);

void isSymmetric(Relation *relation);

void isAntiSymmetric(Relation *relation);

void isTransitive(Relation *relation);

void isFunction(Relation *relation);

void domain(Relation *relation);

void codomain(Relation *relation);

bool isInjective(Relation *relation, Set *setA, Set *setB, bool printResult);

bool isSurjective(Relation *relation, Set *setA, Set *setB, bool printResult);

void isBijective(Relation *relation, Set *setA, Set *setB);

bool containsRelationPair(Relation *relation, RelationPair relationPair);

bool empty(Set *set) {
    for (int j = 0; j < set->cardinality; ++j) {
        printf("%s ", set->items[j]);
        //printf("%s )", set->items[j]);
    }
    printf(" \n");
}

int card(Set *set) {
    printf("noice\n");
}

int complement(Set *set) {
    printf("noice\n");
}

void _union(Set *setA, Set *setB) {
    printf("noice\n");
}

int intersect(Set *setA, Set *setB) {
    printf("noice\n");
}

int minus(Set *setA, Set *setB) {
    printf("noice\n");
}

bool subseteq(Set *setA, Set *setB) {
    printf("noice\n");
}

bool subset(Set *setA, Set *setB) {
    printf("noice\n");
}

bool equals(Set *setA, Set *setB) {
    printf("noice\n");
}

void *findRelation(RelationArray *relArray, int num) {
    for (int i = 0; i < relArray->length; i++) {
        if (relArray->relations[i]->id == num) {
            return relArray->relations[i];
        }
    }
    //  return NULL;
}

void *findSet(SetArray *setArray, int num) {
    for (int i = 0; i < setArray->length; i++) {
        if (setArray->sets[i]->id == num) {
            return setArray->sets[i];
        }
    }
    //return NULL;
}

bool setContains(Set *set, char *item) {
    for (int i = 0; i < set->cardinality; ++i) {
        if (strcmp(set->items[i], item) == 0) {
            return true;
        }
    }

    return false;
}

void printSet(Set *set) {
    printf("S ");
    for (int i = 0; i < set->cardinality; ++i) {
        printf("%s", set->items[i]);

        if (i != set->cardinality - 1) {
            printf(" ");
        }
    }

    printf("\n");
}
//void exitProgram()
int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of args\n");
        exit(EXIT_FAILURE);
    }

    printf("Arg: %s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");

    SetArray setArray;
    setArray.length = 0;
    setArray.sets = NULL;

    RelationArray relArray;
    relArray.length = 0;
    relArray.relations = NULL;

    Set *universum;
    Set *tmpSet;
    Relation *tmpRel;
    RelationPair *tmpRelPair;
    universum = setCreator();
    tmpSet = setCreator();
    tmpRel = relCreator();
    tmpRelPair = relPairCreator();

    char c, type = ' ';
    int cardinality = 0, sequence = 0, lineNum = 0, lineChar = 0;
    char *tmpStr = malloc(1);
    char *tmpRelItem = NULL;
    bool first = false, second = false;
    char *command = NULL;
    char **cmdArgs = NULL;
    int cmdNum = 0;
    while (true) {
        c = fgetc(file);
        lineChar++;
        //printf("C: %d \n", c);
        if (lineChar == 2){
            if(type == 'S' && c == 10){
                tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
                if (tmpStr == NULL)
                    exit(EXIT_FAILURE);
                *(tmpStr + sequence) = 0;
                ++sequence;
                c = '\n';
            } else {
                continue;
            }
            //continue;
        }
        if (type == ' ') {
            if (c != 'U' && c != 'C' && c != 'R' && c != 'S') {
                printf("Unknown command %c in file %s on line %d \n", c, argv[1], lineNum + 1);
                exit(EXIT_FAILURE);
            }
            type = c;
            continue;
        }
        if (c == ' ' || c == '\n' || c == -1) {
            ++cardinality;
            sequence = 0;
            if (type == 'U') {
                setIncrement(universum, tmpStr);
            }
            if (type == 'S') {
                setIncrement(tmpSet, tmpStr);
            }
            if (type == 'R') {
                if (first) {
                    tmpRelPair = malloc(sizeof(tmpStr));
                    tmpRelPair->first = tmpStr;
                    first = false;
                }
                if (second) {
                    tmpRelPair->second = tmpStr;
                    second = false;
                    relIncrement(tmpRel, tmpRelPair);
                    tmpRelPair = NULL;
                }
            }
            if (type == 'C') {
                if (command != NULL) {
                    cmdNum++;
                    cmdArgs = realloc(cmdArgs, sizeof(char *));
                    if (cmdArgs == NULL)
                        exit(EXIT_FAILURE);
                    *(cmdArgs + (cmdNum - 1)) = tmpStr;
                }
                if (command == NULL) command = tmpStr;
            }
            tmpStr = NULL;
            if (c == '\n' || c == -1) {
                lineNum++;
                lineChar = 0;
                cardinality = 0;
                if (type == 'S') {
                    //printf("kokokokook %d\n", lineNum);
                    tmpSet->id = lineNum;
                    setArray.length++;
                    setArray.sets = realloc(setArray.sets, setArray.length * sizeof(Set *));
                    *(setArray.sets + (setArray.length - 1)) = tmpSet;
                    tmpSet = setCreator();
                }
                if (type == 'R') {
                    tmpRel->id = lineNum;
                    relArray.length++;
                    relArray.relations = realloc(relArray.relations, relArray.length * sizeof(Relation *));
                    *(relArray.relations + (relArray.length - 1)) = tmpRel;
                    tmpRel = relCreator();
                }
                if (type == 'C') {
                    int firstArg = 0, secondArg = 0, thirdArg = 0;
                    if (cmdArgs[0] != NULL) firstArg = atoi(cmdArgs[0]);
                    if (cmdArgs[1] != NULL) secondArg = atoi(cmdArgs[1]);
                    if (cmdArgs[2] != NULL) thirdArg = atoi(cmdArgs[2]);
                    printf("Command: %s Args:", command);
                    for (int i = 0; i < cmdNum; i++) {
                        printf(" %s ", cmdArgs[i]);
                    }
                    printf("\n");
                    //Relace
                    if(strcmp(command, "reflexive") == 0){isReflexive(findRelation(&relArray,firstArg), universum);}
                    if(strcmp(command, "symmetric") == 0){isSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "antisymmetric") == 0){isAntiSymmetric(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "transitive") == 0){isTransitive(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "function") == 0){isFunction(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "domain") == 0){domain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "codomain") == 0){codomain(findRelation(&relArray,firstArg));}
                    if(strcmp(command, "injective") == 0){isInjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg), true);}
                    if(strcmp(command, "surjective") == 0){isSurjective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg), true);}
                    if(strcmp(command, "bijective") == 0){isBijective(findRelation(&relArray,firstArg), findSet(&setArray,secondArg),findSet(&setArray, thirdArg));}
                    //Mnoziny
                    if(strcmp(command, "empty") == 0){empty(findSet(&setArray,firstArg));}
                    if(strcmp(command, "card") == 0){card(findSet(&setArray,firstArg));}
                    if(strcmp(command, "complement") == 0){complement(findSet(&setArray,firstArg));}
                    if(strcmp(command, "union") == 0){_union(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    if(strcmp(command, "intersect") == 0){intersect(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    if(strcmp(command, "minus") == 0){minus(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    if(strcmp(command, "subseteq") == 0){subseteq(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    if(strcmp(command, "subset") == 0){subset(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    if(strcmp(command, "equals") == 0){equals(findSet(&setArray,firstArg),findSet(&setArray, secondArg));}
                    //reset
                    command = NULL;
                    cmdNum = 0;
                    cmdArgs = NULL;
                }
                type = ' ';
                //command = NULL;
                if(c == -1){
                    if (feof(file))break;
                    break;
                }
            }
            continue;
        }
        if (type == 'R') {
            if (c == '(') {
                first = true;
                continue;
            }
            if (c == ')') {
                second = true;
                continue;
            }
        }
        tmpStr = realloc(tmpStr, (sequence + 1) * sizeof(char));
        if (tmpStr == NULL)
            exit(EXIT_FAILURE);
        *(tmpStr + sequence) = c;
        ++sequence;
    }

    //Print
    printf("Universum: ");
    for (int i = 0; i < universum->cardinality; ++i) {
        printf("%s ", universum->items[i]);
    }
    printf("\n");
    for (int i = 0; i < setArray.length; ++i) {
        printf("set %d (", setArray.sets[i]->id);
        for (int j = 0; j < setArray.sets[i]->cardinality; ++j) {
            printf(" %s ", setArray.sets[i]->items[j]);
        }
        printf(")\n");
    }

    for (int i = 0; i < relArray.length; ++i) {
        printf("Rel %d ", relArray.relations[i]->id);
        for (int j = 0; j < relArray.relations[i]->cardinality; ++j) {
            printf("( %s ", relArray.relations[i]->items[j]->first);
            printf("%s )", relArray.relations[i]->items[j]->second);
        }
        printf("\n");
    }

    codomain(relArray.relations[0]);
    //Memory dealoc
    setDestructor(universum);
    setDestructor(tmpSet);
    //relDestructor(tmpRel);
   // relPairDestructor(tmpRelPair);
    for(int i = 0; i < relArray.length; i++){
        for(int j = 0; j < relArray.relations[i]->cardinality; j++){
            relPairDestructor(relArray.relations[i]->items[j]);
        }
        relDestructor(relArray.relations[i]);
        //relArray.relations[i];
    }
    for(int i = 0; i < setArray.length; i++){
        setDestructor(setArray.sets[i]);
    }
    free(tmpStr);
    free(cmdArgs);
    free(relArray.relations);
    free(setArray.sets);

}


// Rel functions
void isReflexive(Relation *relation, Set *universum) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < universum->cardinality; ++i) {
        tmpPair.first = universum->items[i];
        tmpPair.second = universum->items[i];
        if (!containsRelationPair(relation, tmpPair)) {
            result = false;
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void isSymmetric(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        tmpPair.first = relation->items[i]->second;
        tmpPair.second = relation->items[i]->first;
        if (strcmp(relation->items[i]->first, relation->items[i]->second) != 0) {
            if (!containsRelationPair(relation, tmpPair)) {
                result = false;
                break;
            }
        }
    }
    printf("%s", result ? "true" : "false");
}

void isAntiSymmetric(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        tmpPair.first = relation->items[i]->second;
        tmpPair.second = relation->items[i]->first;
        if (strcmp(relation->items[i]->first, relation->items[i]->second) != 0) {
            if (containsRelationPair(relation, tmpPair)) {
                result = false;
                break;
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}


void isTransitive(Relation *relation) {
    bool result = true;
    RelationPair tmpPair;
    for (int i = 0; i < relation->cardinality; ++i) {
        for (int j = 0; j < relation->cardinality; ++j) {
            tmpPair.first = relation->items[i]->first;
            tmpPair.second = relation->items[j]->second;
            if (strcmp(relation->items[i]->second, relation->items[j]->first) == 0) {
                if (!containsRelationPair(relation, tmpPair)) {
                    result = false;
                    break;
                }
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void isFunction(Relation *relation) {
    bool result = true;

    for (int i = 0; i < relation->cardinality; ++i) {
        for (int j = 0; j < relation->cardinality; ++j) {
            if (i == j) {
                continue;
            }

            if (strcmp(relation->items[i]->first, relation->items[j]->first) == 0) {
                result = false;
                break;
            }
        }
    }
    printf("%s\n", result ? "true" : "false");
}

void domain(Relation *relation) {
    Set *domain = setCreator();

    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(domain, relation->items[i]->first)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->first[j];
            }
            setIncrement(domain, newStr);
            newStr = NULL;
        }
    }

    printSet(domain);
    setDestructor(domain);
}

void codomain(Relation *relation) {
    Set *codomain = setCreator();

    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            }
            setIncrement(codomain, newStr);
            newStr = NULL;
        }
    }

    printSet(codomain);
    setDestructor(codomain);
}

bool isInjective(Relation *relation, Set *setA, Set *setB, bool printResult) {
    bool result = true;
    Set *codomain = setCreator();
    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(setA, relation->items[i]->first) || !setContains(setB, relation->items[i]->second)) {
            continue;
        }
        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            }
            setIncrement(codomain, newStr);
            newStr = NULL;
        } else {
            result = false;
            break;
        }
    }

    setDestructor(codomain);
    if (printResult) {
        printf("%s\n", result ? "true" : "false");
    }
    return result;
}

bool isSurjective(Relation *relation, Set *setA, Set *setB, bool printResult) {
    bool result = true;

    Set *codomain = setCreator();
    for (int i = 0; i < relation->cardinality; ++i) {
        if (!setContains(setA, relation->items[i]->first) || !setContains(setB, relation->items[i]->second)) {
            continue;
        }

        if (!setContains(codomain, relation->items[i]->second)) {
            unsigned long int length = strlen(relation->items[i]->second);
            char *newStr = malloc(length * sizeof(char));
            for (int j = 0; j < length; j++) {
                *(newStr + j) = relation->items[i]->second[j];
            }
            setIncrement(codomain, newStr);
            newStr = NULL;
        } /* else {
            result = false;
            break;
        } */
    }

    result = setB->cardinality == codomain->cardinality;
    setDestructor(codomain);
    if (printResult) {
        printf("%s\n", result ? "true" : "false");
    }
    return result;
}

void isBijective(Relation *relation, Set *setA, Set *setB) {
    if (setB->cardinality != setA->cardinality) {
        printf("false\n");
        return;
    }

    bool result = isInjective(relation, setA, setB, false) && isSurjective(relation, setA, setB, false);

    printf("%s\n", result ? "true" : "false");
}

bool containsRelationPair(Relation *relation, RelationPair relationPair) {
    for (int i = 0; i < relation->cardinality; ++i) {
        if (strcmp(relation->items[i]->first, relationPair.first) == 0 &&
            strcmp(relation->items[i]->second, relationPair.second) == 0) {
            return true;
        }
    }

    return false;
};