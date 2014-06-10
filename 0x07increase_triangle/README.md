
the struct of increase_triangle_t demo
{
[cur_layer=1]		base_value*(multiple^(cur_layer-1))
[cur_layer=2]		base_value*(multiple^(cur_layer-1))	base_value*(multiple^(cur_layer-1))
[cur_layer=3]		base_value*(multiple^(cur_layer-1)) base_value*(multiple^(cur_layer-1)) base_value*(multiple^(cur_layer-1))
[cur_layer=4]		base_value*(multiple^(cur_layer-1)) base_value*(multiple^(cur_layer-1)) base_value*(multiple^(cur_layer-1)) base_value*(multiple^(cur_layer-1))
...................................................................................................................................................................
[cur_layer=layers]	base_value*(multiple^(cur_layer-1))*cur_layer

for example:
layers=4;
base_value=8;
multiple=2;

8
16    16
32    32    32
64    64    64    64
}