+ 处理不同图像时需要稍微修改代码，如下：

			处理灰度图像时： typedef short         PixelType;
			处理二值图像时：  typedef unsigned char     PixelType;

+ 执行方法如下：

			./main firstSliceValue lastSliceValue  outputImageFile
