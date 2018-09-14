# -*- coding: utf-8 -*-
"""
Created on Fri Sep 14 09:12:16 2018

@author: peter
"""

import matplotlib.pyplot as plt
date=['2018-5','2018-6','2018-7','2018-8']
number=[27,100,202,75]
plt.title("时间与文章阅读数",fontproperties='SimHei',fontsize=25)
plt.xlabel("时间",fontproperties='SimHei',fontsize=15)
plt.ylabel("文章阅读数",fontproperties='SimHei',fontsize=15)
plt.plot(date,number)