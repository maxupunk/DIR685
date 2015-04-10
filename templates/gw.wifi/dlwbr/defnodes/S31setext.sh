#!/bin/sh
#widget
xmldbc -x /runtime/widget/salt      "get:widget -s"
xmldbc -x /runtime/widget/hash      "get:widget -a /var/run/password"
xmldbc -x /runtime/time/dateddyymm	"get:date +%d,%b,%Y"
