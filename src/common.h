#ifndef COMMON_H
#define COMMON_H

// Box2D works best for objects of size 0.1m ... 10m
// So we have a miniature world this time, makes easier to make things happen when
// used forces are not too big, and nothing too surprising should not happen either...
// 16px = 0.1m
// this makes our main character as 32px * 64px ( 20cm wide and 40cm tall )
#define _PMF (0.1f / 16.0f)

#define P2M(x) ((x) * (_PMF))
#define M2P(x) ((x) / (_PMF))

#define FPS 60
#define FRAME_INTERVAL (1000 / FPS)

#endif
