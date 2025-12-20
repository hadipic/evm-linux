## 生命周期

在页面EVUE文件中可以定义如下页面生命周期函数：

| 属性 | 描述 | 	触发时机 |
| :-----| ----: | :----: |
| onInit | 页面初始化 | 页面数据初始化完成时触发，只触发一次。 |
| onReady | 页面创建完成 | 页面创建完成时触发，只触发一次。 |
| onShow | 页面显示 | 页面显示时触发。 |
| onHide | 页面消失 | 页面消失时触发。 |
| onDestroy | 页面销毁 | 页面销毁时触发。 |


```html
<div class="item-container">
  <text class="item-title">Image Show</text>
  <div class="item-content">
    <image src="/common/xxx.png" class="image"></image>
  </div>
</div>
<script>
data = {
    
}

def onInit():
    pass

def onReady():
    pass

def onShow():
    pass

def onHide():
    pass

def onDestroy():
    pass
</script>
```