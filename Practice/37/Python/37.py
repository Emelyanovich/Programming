import math
import copy

def equal(a, b, e=1E-10):
    if -e < a - b < e: return True
    else: return False

PRECISION = 1e+10

class Point:
    def __init__(self, a1 = 0, a2 = 0, coord_system = 'Cartesian'):
        if type(a1) == str:
            p = a1.find(',')
            self.x = float(a1[1 : p].strip())
            self.y = float(a1[p+1 : -2].strip())
            return

        if (coord_system == 'Cartesian'):
            self.x = a1
            self.y = a2
            return
        else:
            self.x = math.cos(a2) * a1
            self.y = math.sin(a2) * a1

    def __eq__(self, p):
        return type(p) == Point and ((math.trunc(self.x * PRECISION) / PRECISION) == (math.trunc(p.x * PRECISION) / PRECISION) and
               (math.trunc(self.y * PRECISION) / PRECISION) == (math.trunc(p.y * PRECISION) / PRECISION))

    def __ne__(self, p):
        return type(p) == Point and ((math.trunc(self.x * PRECISION) / PRECISION) != (math.trunc(p.x * PRECISION) / PRECISION) and
               (math.trunc(self.y * PRECISION) / PRECISION) != (math.trunc(p.y * PRECISION) / PRECISION))

    def get_x(self):
        return self.x
        
    def set_x(self, x):
        self.x = x

    def get_y(self):
        return self.y
        
    def set_y(self, y):
        self.y = y

    def get_r(self):
        return math.hypot(self.x, self.y)
        
    def set_r(self, r):
        phi = self.get_phi()
        self.x = math.cos(phi) * r
        self.y = math.sin(phi) * r

    def get_phi(self):
        return math.atan2(self.y, self.x)

    def set_phi(self, phi):
        r = self.get_r()
        self.x = math.cos(phi) * r
        self.y = math.sin(phi) * r

    def __repr__(self):
        return f"Point({self.x},{self.y})"

    def __str__(self):
        return f"({self.x},{self.y})"


class Vector:
    point: Point
    
    def __init__(self, begin = None, end = None):
        if begin == None:
            if end == None:
                self.point = Point(1, 0)
            else:
                self.point = end
        else:
            if end == None:
                self.point = begin
            else:
                self.point = Point(end.get_x() - begin.get_x(), end.get_y() - begin.get_y())

    
    def __eq__(self, v):
        return self.point == v.point

    
    def __neg__(self):
        return Vector(Point(-self.point.get_x(), -self.point.get_y()))

    
    def __add__(self, v):
        p = Point()
        p.set_x(self.point.get_x() + v.point.get_x())
        p.set_y(self.point.get_y() + v.point.get_y())
        
        return Vector(p)

    
    def __sub__(self, v):
        p = Point()
        p.set_x(self.point.get_x() - v.point.get_x())
        p.set_y(self.point.get_y() - v.point.get_y())
        
        return Vector(p)

    
    def __mul__(self, v):
        if type(v) == int or type(v) == float:
            p = Point()
            p.set_x(self.point.get_x() * v)
            p.set_y(self.point.get_y() * v)
            
            return Vector(p)
        else:
            return self.length() * v.length() * math.cos(self.point.get_phi() - v.point.get_phi())

    
    def length(self):
        return self.point.get_r()


a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))
if a == b and b == a: print('Equality test passed')
else: print('Equality test failed')
  
na  = Vector(Point(-1, -2))
ox  = Vector(Point( 1,  0))
nox = Vector(Point(-1,  0))
oy  = Vector(Point( 0,  1))
noy = Vector(Point( 0, -1))
if a == -na and na == -a and -ox == nox and -oy == noy: print('Invert test passed')
else: print('Invert test failed')
  
if ox + oy + oy == a and -ox == -a + oy + oy: print('Summation test passed')
else: print('Summation test failed')
  
if -ox + oy == oy - ox and -oy + ox == ox - oy: print('Subtraction test passed')
else: print('Subtraction test failed')
  
if (ox * 3 == ox + ox + ox and
    oy * 3 == oy + oy + oy and
    ox * (-3) == -ox - ox - ox and
    oy * (-3) == -oy - oy - oy): print('Multiplication by number test passed')
else: print('Multiplication by number test failed')
  
if (equal(ox.length(), 1) and
    equal(oy.length(), 1) and
    equal((ox * 3 + oy * 4).length(), 5)): print('Length test passed')
else: print('Length test failed')
  
if (equal(ox*ox, ox.length()**2) and
    equal(oy*oy, oy.length()**2) and
    equal((ox*3 + oy*4)*(ox*3 + oy*4), (ox*3 + oy*4).length()**2)): print('Multiplication by Vector test passed')
else: print('Multiplication by Vector test failed')
