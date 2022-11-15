## HTML语法参考

类似HTML的标记语言，通过组件，事件构建出页面的内容。页面具备数据绑定、事件绑定、列表渲染、条件渲染等高级能力。

#### 页面结构

```html
<div class="item-container">
  <text class="item-title">Image Show</text>
  <div class="item-content">
    <image src="/common/xxx.png" class="image"></image>
  </div>
</div>
```

#### 数据绑定

```html
<div onclick="onclicked">
  <text> {{result} </text>
</div>
```

```python
data = {
    'result': 'hello world'
}

def onclicked(self):
    print('hello world')
```

#### 列表渲染

```html
<div class="array-container">
  <template v-for="item in array">
    <text>{{item.name}}</text>
  </template>
</div>
```

```python
data = {
    'array': [
        {"name": 'jack', 'age': 18}, 
        {"name": 'tony', 'age': 18}
    ]
}
```

#### 条件渲染

```html
<div class="array-container">
  <template v-if="result">
    <text>Hello EVUE</text>
  </template>
</div>
```

```python
data = {
    'result': False
}
```