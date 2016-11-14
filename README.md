## 图谱的训练与分割 ##
## 前言
这个库里面的代码主要是为CT图像器官的图谱建立与分割所服务的，下面主要介绍了，代码如何使用。
## 代码运行脑图
<center>
![代码运行脑图](http://chuantu.biz/t5/39/1477716982x2728309575.png)
</center>
## 每一步的运行过程说明
### 对灰度和二值图像做插值（该步可以跳过）
+ 插值是为了防止在训练的过程出现错误，所以相对灰度和二值图像做插值运算，插值代码在`UpsampleVolume_char-label`和`UpsampleVolume_short-img`文件夹中。
+ `-label`作用二值图像，`-img`作用于灰度图像，使用前需要先`ccmake`和`make`一下进行配置和编译，然后将生成的`main`可执行文件拷贝到需要插值的文件夹中，执行`upsample`脚本文件就可以进行插值运算来，如果脚本文件不能执行需要先给执行权限，`upsample`脚本文件内容如下：

                #!/bin/bash
                mkdir upsample_label
                for ((a=1; a <= 40; a++))
                do
                    ./main label-$a-flip-spleen-roi.nrrd upsample_label/label-$a-flip-spleen-roi-2.nrrd 1 1 2
                done
    
+ 该脚本是作用于二值图像的例子，灰度图像也要重复上述过程。           
###　掩码运算
+ 掩码的代码在`MASKImage`文件夹中，同样使用前需要先`ccmake`和`make`一下进行配置和编译，然后执行`mask-spleen`脚本文件，注意脚本中文件的路径，`mask-spleen`脚本文件内容如下：

            #!/bin/bash
            for ((a=1; a <= 40; a++))
            do
                ./main spleen-roi/upsample_img/img-$a-flip-spleen-roi-2.nrrd 
                spleen-label-roi/upsample_label/label-$a-flip-spleen-roi-2.nrrd mask_result-2/img-$a-flip-spleen-masked.nrrd
            done
            
+ 如图：

![掩码](http://chuantu.biz/t5/39/1477718387x2728309575.png)

### 开始训练
+ 训练的代码在`atlas_*_UAB`文件夹中，先在此文件夹中建`build`文件夹，并在`build`中进行配置和编译。
+ 执行`mkdir_file`脚本，在`build`中生成必要的文件夹，将`elastix`、`parameters_BSpline.txt`、`parameters_Affine.txt`、`transformix`这4个文件拷贝到build中，这个很重要！！！
+ 将掩码后的nrrd文件拷贝到`training`文件夹中，规范命名，将手动挑选的初始模板与第0组交换。
+ 执行编译后生成的`asm`的文件，如图：
![开始训练](http://chuantu.biz/t5/39/1477719142x2728309575.png)
+ 如果运行出错，需要重新下载`elastix`和`transformix`文件，下载方式如下：

            sudo apt-get install elastix
            
+ 然后将`/etc/bin`中的`elastix`和`transformix`文件替换掉原来的`elastix`和`transformix`文件，重新执行`asm`文件。
+ 如果数据很多的话，训练过程需要很久，一、两天也有可能，慢慢等吧。

### 计算图谱
+ 在计算图谱之前需要将最后一次迭代矩阵作用于最初的灰度和二值图像，建两个文件夹‘img_txt’、`label_txt`分别处理灰度和二值图像。
+ 将最后一次训练迭代的矩阵，即最后一次迭代产生的txt文件拷贝到‘img_txt’、`label_txt`文件中。
+ 执行`mkdir_file`脚本，生成必要的文件夹，用`g++`编译.cpp文件，`interpolate0to3.cpp`作用于`img_txt`中的`txt`,`avgTranform.cpp`作用于`label_txt`中的`txt`.如图：
![](http://chuantu.biz/t5/39/1477721257x2728309575.png)
![](http://chuantu.biz/t5/39/1477721290x2728309575.png)
+ 将最初的灰度和二值图像（nrrd）分别拷贝到‘img_txt’、`label_txt`文件中，注意命名方式和将手动挑选的初始模板与第0组交换。
+ 执行`update`脚本，将`txt`作用到`nrrd`上,结果保存在`exampleoutput`中，如图：
![](http://chuantu.biz/t5/39/1477721417x2728309575.png)
+ 将处理后的`nrrd`求平均，得到最终的图谱：`avg.nrrd`。需要先`ccmake`和`make`一下进行配置和编译求平均的代码，得到一个可执行文件`main`.
+ 执行`main`，传的参数为数据集的个数，如图：
![](http://chuantu.biz/t5/39/1477721605x2728309575.png)

### 通过图谱对原始灰度图像进行分割
+ 训练的代码在`MAS_*_UAB_FFD`文件夹中，先在此文件夹中建`build`文件夹，并在`build`中进行配置和编译。
+ 执行`mkdir_file`脚本，在`build`中生成必要的文件夹，将`elastix`、`parameters_BSpline.txt`、`parameters_Affine.txt`、`transformix`这4个文件拷贝到build中，这个很重要！！！
+ 将图谱和要分割的原始灰度图像拷贝到`training`文件夹，灰度图谱命名：`avg.nrrd`,二值图谱命名：`avg_mask.nrrd`,原始灰度图像命名：`liver-0.nrrd`.
+ 在MAS文件夹中建一个文件夹用来保存分割后的结果，命名为：`0`.注：有多少组原始灰度图像，就需要有多少个保存结果的文件，命名方式依次递增。
+ 执行`asm`文件进行分割，如图：
![](http://chuantu.biz/t5/39/1477722468x2728309575.png)
+ 最后分割结果保存在`0`文件夹中，如图：
![](http://chuantu.biz/t5/39/1477722585x2728309575.png)

## 分割ROI篇
### 前言
在`图谱的训练与分割`这篇文章中已经介绍了如何训练图谱以及分割数据，为了使分割结果更加准确引入了`ROI`分割，分割时先要对图谱进行处理，以便适应分割数据。此外本文章还准备结果如何计算分割结果的精度。
###　获取灰度图像的ROI
+ 获取ROI之前需要需要数据对应的坐标，并存放到`roi.txt`文件夹中，并将`roi.txt`与`getROI`的代码可执行文件放到同意路径下，再执行程序便可以得到灰度图像的ｒｏｉ，原始灰度图像和和ROI图像对比如下：
+ 原始灰度图像:
![原始灰度图像](http://chuantu.biz/t5/41/1479106346x3396789373.png)  <br><br>
+ ROI图像:
![ROI图像](http://chuantu.biz/t5/41/1479106405x3396789373.png)   <br><br>
+ 将处理好的ＲＯＩ图像放到分割代码的training文件夹中，注意命名方式，序号从０开始。
### 图谱处理以及分割
+ 使用`3dseg`软件对图谱进行处理，将目标器官分割出来。
+ 注意：用软件对灰度图谱和二值图谱进行分割是，二者的尺寸和坐标要完全一致。
+ 分割完之后也放入`training`文件夹中，命名方式：灰度－`avg.nrrd`;二值－`avg_mask.nrrd`.
+ 接着开始分割，不过需要注意的是，分割数据和图谱都是ROI，并且需要每组分割数据的坐标存放在`roi.txt`文件中,`roi.txt`文件放到`ｂｕｉｌｄ`中。分割代码的执行方式和之前一样，所不同的是会产生两个分割结果：`ＲＯＩ结果`FINALLL.nrrd`，通过坐标处理后的正常大小分割结果`FINALLLL.nrrd`(比前面多了一个L)`。
+ 分割时需要修改如下３个参数：

		bool TUMOR_CASE_USE_PA_EQUAL_ONE = true;   //true/false
		bool Use_Process_Ori_mask_9par = false;   //true/false
		double PAThreshold = 0.2;　　//  0.2/0.9


排列组合有８中可能，所以需要分割８次，保存每次的分割结果，注意最终结果的命名，以便区分。

### 计算精度
+ 运行计算精度的代码时需要另外再下载 `libann-dev`,下载方式如下：

		sudo apt-get install libann-dev
+ 或者用`synatic`直接搜索下载。
+ 然后配置和编译好的计算精度的代码，执行时需要两个参数，批量执行的脚本如下：

		for((a=0;a<=20;a++))
		do
		 ./EvaluateSegmentationResult seg-spleen/FINALLL-$a-0.2-ff.nrrd refer-spleen/label-roi-$a.nrrd
		done
		
+ 执行完之后会产生一个`evaluation.txt`文件，对比精度信息全部存在里面，如下图：
![evaluation.txt](http://chuantu.biz/t5/41/1479108598x3396789373.png)
+ `JI`表示程序分割与手动分割的数据重合率，值越大，说明效果越好，最大是１００．
+ `ASD`表示程序分割与手动分割的数据的边缘距离，值越小，说明效果越好，结果最好是，值为０．