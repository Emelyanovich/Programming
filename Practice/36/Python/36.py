import math
import copy

class coord_systems:
        Cartesian = 0
        Polar = 1

class cartesian_coord:
        def __init__(self, x, y):
                self.x = x
                self.y = y

class polar_coord:
        def __init__(self, r, phi):
                self.r = r
                self.phi = phi

class Point:
        def __init__(self, a1 = 0, a2 = 0, coord_system = coord_systems.Cartesian):
                if type(a1) == str:
                        self.a1, self.a2 = map(float, a1[1:-1].split(","))
                        self.coord_system = coord_systems.Cartesian
                if (type(a1) == int) or (type(a1) == float):
                        self.a1, self.a2 = a1, a2
                        self.coord_system = coord_system

        def __eq__(p1, p2):
                return (abs(p1.a1 - p2.a1) <= 10**-10) and\
                           (abs(p1.a2 - p2.a2) <= 10**-10)

        def __ne__(p1, p2):
                return not (p1 == p2)

        def __repr__(self):
                return "("+str(self.a1)+","+str(self.a2)+")"

        def __str__(self):
                return repr(self)

        def to_cartesian(self, r, phi):
                return cartesian_coord(
                        r * math.cos(phi),
                        r * math.sin(phi)
                )

        def to_polar(self, x, y):
                return polar_coord(
                        math.hypot(x, y),
                        math.atan2(y, x)
                )

        def get_x(self):
                return self.a1 if self.coord_system == coord_systems.Cartesian else self.to_cartesian(self.a1, self.a2).x

        def get_y(self):
                return self.a2 if self.coord_system == coord_systems.Cartesian else self.to_cartesian(self.a1, self.a2).y

        def get_r(self):
                return self.a1 if self.coord_system == coord_systems.Polar else self.to_polar(self.a1, self.a2).r

        def get_phi(self):
                return self.a2 if self.coord_system == coord_systems.Polar else self.to_polar(self.a1, self.a2).phi

        def set_x(self, x):
                if (self.coord_system == coord_systems.Cartesian):
                        self.a1 = x
                else:
                        coord = self.to_polar(x, self.to_cartesian(self.a1, self.a2).y)
                        self.a1 = coord.r
                        self.a2 = coord.phi

        def set_y(self, y):
                if (self.coord_system == coord_systems.Cartesian):
                        self.a2 = y
                else:
                        coord = self.to_polar(self.to_cartesian(self.a1, self.a2).x, y)
                        self.a1 = coord.r
                        self.a2 = coord.phi

        def set_r(self, r):
                if (self.coord_system == coord_systems.Polar):
                        self.a1 = r
                else:
                        coord = self.to_cartesian(r, self.to_polar(self.a1, self.a2).phi)
                        self.a1 = coord.x;
                        self.a2 = coord.y;

        def set_phi(self, phi):
                if (self.coord_system == coord_systems.Polar):
                        self.a2 = phi;
                else:
                        coord = self.to_cartesian(self.to_polar(self.a1, self.a2).r, phi)
                        self.a1 = coord.x
                        self.a2 = coord.y

with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]

simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180*math.pi/180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')
