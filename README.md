# jeeves
codeburners' secretary

So this is the secretary Darrin made for our discord server "Codeburners". He got the idea by watching "The Good Place".
In the show, they have a robot named Janet that is all-knowing and very polite, and he thought we could use one
of those for our discord server. Hence Jeeves.

Jeeves handles lots of Kattis things automatically.

For instance, any time someone sends a file to his channel, he will submit it on kattis and report the
verdict. If a problem is judged correct, he will also add it to his knowledge base for later reference, and mark
the solver for the leaderboard.

In addition to this, Jeeves can also set contests, and recommend problems targeting different subject areas.

Every problem submitted to Jeeves must have an annotation denoting a few things:

1) the problem that is being solved on kattis
2) the methodology used
3) a list of tags, topics related to the problem
4) an explanation of how the problem was solved

This information is stored in a SQL Database Darrin architected, and can be retrieved on command by Jeeves.

Jeeves can also set contests automatically, and generate contest writeups from the solution sketches it has on hand,
which Darrin (and I) find pretty cool.
