from py_utils import BenchmarkResult
import plotly.graph_objects as go

class Plot:
    BAR_COLORS = [
        'rgb(214, 39, 40)',   # cool red
        'rgb(31, 119, 180)',  # cool blue
        'rgb(44, 160, 44)',   # cool green
        'rgb(148, 103, 189)', # cool purple
        'rgb(227, 119, 194)', # cool pink
        'rgb(127, 127, 127)', # cool grey
        'rgb(23, 190, 207)',  # cool cyan
        'rgb(188, 189, 34)',  # cool olive
        'rgb(140, 86, 75)',   # cool brown
        'rgb(255, 152, 150)', # light red
        'rgb(197, 176, 213)', # light purple
        'rgb(196, 156, 148)', # light brown
    ]

    def __init__(self, result: BenchmarkResult):
        self.benchmark = result
        self.plot = Plot._create_graph(result)

    def save_svg(self, path):
        self.plot.write_image(file=path, format='svg', width=1920, height=1080)

    def show(self):
        self.plot.show()
    
    @staticmethod
    def _get_function_major_data(benchmark: BenchmarkResult):
        dataframe = {}
        for opti in benchmark.benchmarks:
            optimization = opti.optimization
            for result in opti.results:
                if result.name not in dataframe:
                    dataframe[result.name] = {}
                dataframe[result.name][optimization] = result.took / 1_000_000  # ns to ms
        return dataframe

    @staticmethod
    def _create_graph(benchmark: BenchmarkResult):
        fig = go.Figure()
        data = Plot._get_function_major_data(benchmark)
        for i, (category, timings) in enumerate(data.items()):
            fig.add_trace(go.Bar(
                x=list(timings.keys()),
                y=list(timings.values()),
                name=category,
                marker_color=Plot.BAR_COLORS[(i % len(Plot.BAR_COLORS))],
                textposition='auto',
                textfont=dict(size=12)  # Small font for text on bars
            ))
        
        fig.update_layout(
            title=dict(
                text=f"{benchmark.title}<br><sup>(Lower is faster)</sup>",
                x=0.5,
                y=0.95,
                xanchor='center',
                yanchor='top',
            ),
            yaxis_title="Time (ms)",
            yaxis=dict(
                type='log',
                tickformat="f",
                showexponent='all',
                tickfont=dict(size=13),
            ),
            barmode='group',
            margin=dict(t=0, b=350, l=50),
            legend=dict(
                x=0, y=-0.1, orientation='h',
                font=dict(size=30, color='black')
            ),
            template='simple_white',
            font=dict(size=25)  # 1.5 times the default size (12px * 1.5 = 18px)
        )

        benchmark_info = ""
        benchmark_info += f"Compiler info: {benchmark.compiler_info}<br>"
        benchmark_info += f"Build command: {benchmark.build_command}<br>"
        benchmark_info += f"System information:<br>"
        for key, value in benchmark.system_information.items():
            benchmark_info += f" - {key}: {value}<br>"

        fig.add_annotation(
            text=benchmark_info,
            xref="paper", yref="paper",
            showarrow=False,
            font=dict(size=15, color='grey'),
            align='left',
            xanchor='left',
            yanchor='top',
            x=0,
            y=-0.19
        )

        return fig



