#ifndef COMPARISON_H
#define COMPARISON_H

/**
  A type of a function that returns a basic comparison between two elements.

  A basic comparison must return:
    * 1, if the first element is greater than the second;
    * 0, if the first element is equals to the second;
    * -1, if the first element is smaller than the second;
*/
typedef char (*ComparisonFunction)(void * const, void * const);


/**
  A type of a function that returns a distance between two elements.

  If the distance is:
    * zero, the elements are equal;
    * positive, the first element is greater than the second;
    * negative, the first element is smaller than the second;
*/
typedef double (*DistanceFunction)(void * const, void * const);

#endif
