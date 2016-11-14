+ 运行前先执行脚本mkdir
+ 然后将图谱和待分割的数据放到training中，在MAS中建和分割数据对应的文件夹

+ 需要修改如下３个参数：

		bool TUMOR_CASE_USE_PA_EQUAL_ONE = true;   //true/false
		bool Use_Process_Ori_mask_9par = false;   //true/false
		double PAThreshold = 0.2;　　//  0.2/0.9


+ 排列组合有８中可能，所以需要分割８次，保存每次的分割结果，注意最终结果的命名，以便区分。

