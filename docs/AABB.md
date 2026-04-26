AABB = Axis-Aligned Bounding Box.

The main idea is, Every object has a invisible bounding box around that. And the bounding box collide with each other if both axis collide.

`
If all are ture, then A and B collide:

A.left < B.right
A.right > B.left
A.bottom < B.top
A.top > B.bottom
`
