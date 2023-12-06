import numpy as np
import svar
ivox3d = svar.load("ivox3d")
# resolution, inv_resolution, NearbyType, capacity
options = ivox3d.IVoxOption(0.2, 10.0, 1, 5e6)
# init a ivox
ivox = ivox3d.IVox(options)

XYZ = np.random.rand(300000*3)
# add points
ivox.AddPoints(XYZ.tolist())
# query nearest point
ret = ivox.GetClosestPoint([1.0, 0.0, 0.0])
print(ret)
# query nearest N point with max distance
ret = ivox.GetClosestPoints([1.0, 0.0, 0.0], 5, 0.5 )
print(ret)