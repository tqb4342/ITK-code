+ 掩码运算，运行脚本如下：

			#!/bin/bash
			for ((a=1; a <= 40; a++))
			do
			    ./main spleen-roi/spleen-roi-2/img-$a-flip-spleen-roi-2.nrrd spleen-label-roi/spleen-label-roi-2/label-$a-flip-spleen-roi-2.nrrd upsample-mask-result/img-$a-flip-spleen-masked.nrrd
			done
			
