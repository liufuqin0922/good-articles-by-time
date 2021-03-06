# -*- coding: utf-8 -*-
"""
Created on Fri Sep 14 09:12:16 2018

@author: peter
"""

import matplotlib.pyplot as plt
date=['2018-5','2018-6','2018-7','2018-8','2018-9','2018-10','2018-11','2018-12',
    '2019-1','2019-2','2019-3']
number=[27,100,202,75,310,387,265,226,
        186,142,110]
print("total number: ",sum(number))
plt.title("时间与文章阅读数",fontproperties='SimHei',fontsize=25)
plt.xlabel("时间",fontproperties='SimHei',fontsize=15)
plt.ylabel("文章阅读数",fontproperties='SimHei',fontsize=15)
plt.gcf().autofmt_xdate()
plt.plot(date,number)