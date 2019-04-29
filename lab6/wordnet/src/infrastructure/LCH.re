let calculate = (~shortestPath: int, ~depth: int=11, ()) =>
  if (shortestPath == 0) {
    None;
  } else {
    Some(-. log(float_of_int(shortestPath) /. (2. *. float_of_int(depth))));
  };