import numpy as np
from scipy.spatial import distance

# radius: 采样点之间的最小距离
# width, height: 采样区域的宽度和高度
# k: 在放弃前尝试生成新采样点的次数

def poisson_disk_sampling(radius, width, height, k=30):
    cell_size = radius / np.sqrt(2)
    grid_width, grid_height = int(np.ceil(width / cell_size)), int(np.ceil(height / cell_size))
    grid = [None] * (grid_width * grid_height)

    def get_cell_coords(pt):
        return int(pt[0] / cell_size), int(pt[1] / cell_size)

    def get_cell_index(pt):
        x, y = get_cell_coords(pt)
        return x + y * grid_width

    def in_neighbourhood(pt):
        cell_x, cell_y = get_cell_coords(pt)
        for i in range(max(cell_x - 2, 0), min(cell_x + 3, grid_width)):
            for j in range(max(cell_y - 2, 0), min(cell_y + 3, grid_height)):
                idx = i + j * grid_width
                if grid[idx] is not None and distance.euclidean(pt, grid[idx]) < radius:
                    return True
        return False

    pt = np.random.uniform(0, [width, height])
    points, pts_to_process = [pt], [pt]
    grid[get_cell_index(pt)] = pt

    while pts_to_process:
        pt_idx = np.random.randint(len(pts_to_process))
        pt = pts_to_process.pop(pt_idx)
        for _ in range(k):
            new_pt = pt + np.random.uniform(-radius, radius, 2)
            if 0 <= new_pt[0] < width and 0 <= new_pt[1] < height and not in_neighbourhood(new_pt):
                points.append(new_pt)
                pts_to_process.append(new_pt)
                grid[get_cell_index(new_pt)] = new_pt

    return points

# Usage
radius = 10
width, height = 100, 100
points = poisson_disk_sampling(radius, width, height)

# Normalize points to [-1, 1]
normalized_points = [(pt[0] / width * 2 - 1, pt[1] / height * 2 - 1) for pt in points]
# print(normalized_points)
#trun the points to glsl V2 string format
glsl_points = ""
for pt in normalized_points:
    glsl_points += "vec2(%f, %f),\n" % (pt[0], pt[1])
print(glsl_points)

