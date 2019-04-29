let calculate = (~shortestPath: int, ~depth: int=11, ()) => {
  if (shortestPath == 0) 0.
  else -. log(float_of_int(shortestPath) /. (2. *. float_of_int(depth)));
};