#!/usr/local/bin/python3
# 20200831T22:54:21

import json
with open("scene.props") as jfp:
    p = json.load(jfp)
props = p['properties']

with open(props['infilename']) as fp:
    lines = fp.readlines()

cmds=[]
for i in range(0,props['iterations']):
    out = "%s%04d.%s" % (props['outfilename'], i, props['outfileextension'])
    gen = "%s%04d.%s" % (props['outfilename'], i, props['genfileextension'])
    cmds.append("%s %s %s" % (props['executable'], out, gen))
    with open(out, 'w') as sc:
        for l in lines:
            for p0 in p['patterns']:
                if (l.startswith(p0['searchFor'])):
                    a = l.split()
                    v = int(a[p0['index']]) + (int(p0['increment']) * i)
                    a[p0['index']] = str(v)
                    l = ' '.join(a)
            sc.write(l)

for cmd in cmds:
    print(cmd)
