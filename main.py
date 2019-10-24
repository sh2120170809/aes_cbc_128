# check merge function!
# -*- coding: utf-8 -*-
# @File  : main.py
# @Author: shanghui
# @Date  : 2019/09/20
# @Desc  : train_108401.csv是训练数据， test.csv是测试数据（截取了600条训练数据）， result.csv是预测结果
# Need: 需要安装pandas, numpy, xgboost和sklearn: pip install xgboost/pandas/numpy/xgboost/sklearn
# 运行方式: .csv数据不需要任何修改，只需修改路径即可。数据分为训练和测试集

import pandas as pd
import matplotlib.pyplot as plt
import xgboost as xgb
import numpy as np
from xgboost import plot_importance
from sklearn.preprocessing import Imputer


def loadDataset(filePath):
    df = pd.read_csv(filepath_or_buffer=filePath)
    return df


def featureSet(data):
    data_num = len(data)
    XList = []
    for row in range(0, data_num):
        tmp_list = []
        # 我只选部分，其他数据都是相同的值，不清楚具体什么意思，需要添加特征，按以下方法添加就行
        # tmp_list.append(data.iloc[row]['xxxxxxxx'])
        # X,Y,Altitude,Building Height,Clutter Index,RSRP
        tmp_list.append(data.iloc[row]['X'])
        tmp_list.append(data.iloc[row]['Y'])
        tmp_list.append(data.iloc[row]['Altitude'])
        tmp_list.append(data.iloc[row]['Building Height'])
        tmp_list.append(data.iloc[row]['Clutter Index'])
        XList.append(tmp_list)
    # label值（数据的最后一列）
    yList = data[data.columns[-1]]
    #print(yList)
    return XList, yList


def loadTestData(filePath):
    data = pd.read_csv(filepath_or_buffer=filePath)
    data_num = len(data)
    XList = []
    for row in range(0, data_num):
        tmp_list = []
        # X,Y,Altitude,Building Height,Clutter Index,RSRP
        tmp_list.append(data.iloc[row]['X'])
        tmp_list.append(data.iloc[row]['Y'])
        tmp_list.append(data.iloc[row]['Altitude'])
        tmp_list.append(data.iloc[row]['Building Height'])
        tmp_list.append(data.iloc[row]['Clutter Index'])
        XList.append(tmp_list)
    return XList


def trainandTest(X_train, y_train, X_test):
    # XGBoost训练过程， 具体参数含义参考官方文档 https://github.com/dmlc/xgboost/blob/master/doc/parameter.rst
    model = xgb.XGBRegressor(max_depth=6, learning_rate=0.1, n_estimators=1600, silent=False, verbosity = 3, objective='reg:squarederror')
    model.fit(X_train, y_train)

    # 对测试集进行预测
    ans = model.predict(X_test)

    ans_len = len(ans)
    # 输出ID号
    id_list = np.arange(1, ans_len+1)
    data_arr = []
    for row in range(0, ans_len):
        data_arr.append([int(id_list[row]), ans[row]])
    np_data = np.array(data_arr)

    # 写入文件
    pd_data = pd.DataFrame(np_data, columns=['id', 'predict value'])
    # print(pd_data)
    pd_data.to_csv('/Users/shanghui/Desktop/WORK/CODE/XGBOOST/result.csv', index=None)

    # 显示重要特征
    #plot_importance(model)
    #plt.show()

if __name__ == '__main__':
    trainFilePath = '/Users/shanghui/Desktop/WORK/CODE/XGBOOST/data/train_108401.csv'
    testFilePath = '/Users/shanghui/Desktop/WORK/CODE/XGBOOST/data/test.csv'
    data = loadDataset(trainFilePath)
    #print(data)
    X_train, y_train = featureSet(data)
    X_test = loadTestData(testFilePath)
    trainandTest(X_train, y_train, X_test)
