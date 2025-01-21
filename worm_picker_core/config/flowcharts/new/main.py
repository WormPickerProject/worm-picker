"""
main.py

Entry point to create and render the modern task flowchart
using the flowchart_builder module.
"""

import os
from flowchart_builder import create_modern_flowchart


def main() -> None:
    """
    Main function to create and render the flowchart as a PNG file.
    The rendered file is saved in the same directory as this script.
    """
    flowchart = create_modern_flowchart()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(script_dir, 'modern_task_flowchart')

    # Renders the flowchart as 'modern_task_flowchart.png'
    flowchart.render(file_path, view=False, cleanup=True)


if __name__ == "__main__":
    main()