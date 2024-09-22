# md2html

Creates a HTML file for a provided Markdown file.

If test.md is the input file and contains:

```md
# Title

Some contents here.

Some supporting contents here.

## Introduction

May be something here.
```

Then a test.html file is produced containing:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <nav>
        <h1>Arktetra</h1>
    </nav>
    <hr>
    <div class = "content">
        <h1>Title</h1>
        <p>Some contents here.</p>
        <p>Some supporting contents here.</p>
        <h2>Introduction</h2>
        <p>May be something here.</p>
    </div>
    <hr>
</body>
</html>

```
