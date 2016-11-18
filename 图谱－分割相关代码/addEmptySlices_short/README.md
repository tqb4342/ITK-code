+ 当图谱分割的结果不好的时候，可以使用向图谱中间插入片数的方法来时分割结果变得更好，该程序是向灰度图谱插入片数。


		int newDepth = depth + 37;
			createEmptyImage( emptyImage, width, height, newDepth );
			
+ 可以手动修改程序中的height。
+ 需要传入两个参数：输入数据名和输出数据名。