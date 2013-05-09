#ifndef __TYPECHECKTYPE_H__
#define __TYPECHECKTYPE_H__

typedef struct typeCheckType_ *TypeCheckType;
/**
 * Defines a structure for the type of a node in the tree to be used while typechecking. Indeterminable
 * is reserved for those situations where the nature of knode makes it impossible to determine the type.
 * If at all possible try to avoid the use of indeterminable because those will cause headaches during
 * code generation.
 *
 * int, double, string, char, node, edge, and dict should all be fairly straightforward types.
 *
 * For arrays, set "ar_sub" to be another TypeCheckType of the type the array is. If its an array of
 * arrays then "sub" should be another array_ type with another sub and so on.
 *
 * For functions, use fn_sub, with the first fn_sub being the return type of the function and each
 * subsequent fn_sub being the type of each argument. In the event that an argument is an array, use
 * the ar_sub to denote its type as mentioned above.
 */
struct typeCheckType_ {
  enum {indeterminable, int_, double_, string_, char_, node_, edge_, dict_, function_, array_} base;
  TypeCheckType ar_sub;
  TypeCheckType fn_sub;
};

#endif
