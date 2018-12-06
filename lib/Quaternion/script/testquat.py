import Quaternion as q
q = q.quatd(0, 1, 0, 0);
r = q.rotation(15, 0, 1, 0);
print(1, q)
for i in range(1, (360+15)//15):
    q = ~r * q * r
    print(i+1, q)
