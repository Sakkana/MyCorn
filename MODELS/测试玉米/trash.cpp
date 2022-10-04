get boundary of x, y, z axis
    (x_min, y_min, z_min)
    (x_max, y_max, z_max)

normalization
    -1 <= x, y, z <= 1

map
    (x, y, z) -> ((π + atan2(z, x)) / (2 * π), (1 + y) / 2, 1)