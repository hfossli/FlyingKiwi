FlyingKiwi
==========

A wrapper around [Kiwi](https://github.com/nucleic/kiwi), the efficient cassowary constraint solver. 

## Architecture

This is a wrapper around Kiwi. The Kiwi solver and internals is not visible though the FlyingKiwi namespace. 

## Features

#### Constants

Read about my motivation for this feature [here](https://github.com/Overconstrained/cassowary-proposals/blob/master/Proposals/proposal-001.md).

```cplusplus
Constant c1("c1");
Constant c2("c2");
c1.setValue(6.28);
c2.setValue(0.5);

Variable v1("v1");
Expression expression(-v1, SimpleTerm(c1, OP_MULTIPLY, c2));  /*   <-- new possibilities compared with plain Kiwi  */
Constraint constraint(expression, Constraint::RelationalOperator::OP_EQ);

Solver solver;
solver.addConstraint(constraint);
solver.updateVariables();
EXPECT_EQ(v1.value(), 3.14);

c1.setValue(50.0);  /*  <-- changing the constants yields new results  */
solver.reevaluateConstants();
solver.updateVariables();
EXPECT_EQ(v1.value(), 25);

c2.setValue(1.0);  /*  <-- changing the constants yields new results  */
solver.reevaluateConstants();
solver.updateVariables();
EXPECT_EQ(v1.value(), 50.0);
```

## Status quo

It is not ready for production yet. I'll try to keep the issues tab as updated as possible.


## Road ahead

Bugs and incomplete features such as full support for operators will be tracked on the issues tab here on github.

#### New feature: Conditionals

I will port my Objective-C implementation where we are able to say

```objc
[self.solver if:^BOOL {
     return container.width > 200;
} then:{
    title.top == 30,
} else:{
    title.top == 50,
}];
```


