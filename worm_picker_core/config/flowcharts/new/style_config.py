"""
style_config.py

This module defines all styling configurations for the flowchart,
including color palette, node styles, subgraph (cluster) styles,
and edge styles.
"""

from typing import Dict


def get_colors() -> Dict[str, str]:
    """
    Returns a dictionary of Tailwind-inspired colors
    for consistent use across the flowchart.
    """
    return {
        'primary': '#2563EB',     # Strong blue for primary actions/main flow
        'secondary': '#3B82F6',   # Softer blue for supporting elements
        'success': '#059669',     # Muted green for positive outcomes
        'error': '#DC2626',       # Bright red for error states
        'warning': '#D97706',     # Deep amber for decision points
        'background': '#F8FAFC',  # Cool gray for subtle container backgrounds
        'text': '#1E293B',        # Deep slate for primary text
        'light_text': '#64748B',  # Medium slate for secondary text
        'border': '#E2E8F0',      # Light cool gray for subtle boundaries
    }


def get_node_styles(colors: Dict[str, str]) -> Dict[str, Dict[str, str]]:
    """
    Returns a dictionary mapping node types to their respective styles.
    """
    return {
        'process': {
            'style': 'filled,rounded',
            'fillcolor': '#F1F5F9',
            'color': colors['primary'],
            'fontcolor': colors['text'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        },
        'decision': {
            'style': 'filled',
            'fillcolor': '#FEF3C7',
            'color': colors['warning'],
            'fontcolor': colors['text'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'diamond',
            'height': '0.7',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15'
        },
        'error': {
            'style': 'filled,rounded',
            'fillcolor': '#FEE2E2',
            'color': colors['error'],
            'fontcolor': colors['error'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        },
        'success': {
            'style': 'filled,rounded',
            'fillcolor': '#DCFCE7',
            'color': colors['success'],
            'fontcolor': colors['success'],
            'fontname': 'Arial',
            'fontsize': '14',
            'shape': 'box',
            'height': '0.5',
            'width': '1.6',
            'penwidth': '1.5',
            'margin': '0.15,0.1'
        }
    }


def get_subgraph_attrs(colors: Dict[str, str]) -> Dict[str, str]:
    """
    Returns the attributes used for creating a subgraph/cluster.
    """
    return {
        'style': 'rounded,filled',
        'fillcolor': colors['background'],
        'color': colors['border'],
        'fontname': 'Arial',
        'fontsize': '16',
        'fontcolor': colors['text'],
        'labeljust': 'r',
        'labelloc': 't',
        'margin': '20',
        'penwidth': '1.0'
    }


def get_edge_attrs(colors: Dict[str, str]) -> Dict[str, str]:
    """
    Returns the default attributes for edges used in the flowchart.
    """
    return {
        'color': colors['secondary'],
        'penwidth': '1.2',
        'arrowsize': '0.8',
        'arrowhead': 'vee',
        'minlen': '1.5',
        'labelboxstyle': 'rounded,filled',
        'labelbgcolor': '#FFFFFF',
        'labelboxcolor': colors['secondary'],
        'labelboxpenwidth': '1.0',
        'labelboxmargin': '0.1'
    }