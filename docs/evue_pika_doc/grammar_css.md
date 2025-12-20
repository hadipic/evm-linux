## CSS语法参考

CSS是描述HML页面结构的样式语言。所有组件均存在系统默认样式，也可在页面CSS样式文件中对组件、页面自定义不同的样式。

#### 声明样式
每个页面目录下存在一个与布局hml文件同名的css文件，用来描述该hml页面中组件的样式，决定组件应该如何显示。

+ 使用style属性来控制组件的样式。例如：
```html
<div class="container">
  <text style="color: red">Hello World</text>
</div>
```

+ 使用class属性来控制组件的样式。例如：
```html
<div class="container">
  <text style="color: red">Hello World</text>
</div>

<style>
.container {
  background-color: blue;
}
</style>
```

#### 选择器

|  选择器   | 样例  | 样例描述 |
|  ----  | ----  | ----  |
| .class  | .container |用于选择class="container"的组件。 |
| #id  | #titleId | 用于选择id="titleId"的组件。 |

```html
<div id="containerId" class="container">
  <text id="titleId" class="title">标题</text>
  <div class="content">
    <text id="contentId">内容</text>
  </div>
</div>

<style>
.title {
  font-size: 30px;
}

#contentId {
  font-size: 20px;
}
</style>
```