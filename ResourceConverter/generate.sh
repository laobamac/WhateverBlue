#!/bin/bash

#  generate.sh
#  WhateverBlue
#
#  Copyright © 2018 vit9696. All rights reserved.

ret=0

rm -f "${PROJECT_DIR}/WhateverBlue/kern_resources.cpp"

"/Users/laobamac/Desktop/WhateverBlue/ResourceConverter/ResourceConverter" \
	"/Users/laobamac/Desktop/WhateverBlue/Resources" \
	"/Users/laobamac/Desktop/WhateverBlue/WhateverBlue/kern_resources.cpp" \
	"/Users/laobamac/Desktop/WhateverBlue/WhateverBlue/kern_resources.hpp" || ret=1

if (( $ret )); then
	echo "Failed to build kern_resources.cpp"
	exit 1
fi
