import numpy as np
import plotly.graph_objects as go
import streamlit as st
import cpp_bridge

st.set_page_config(page_title="Black-Scholes Pricing", layout="wide")

st.markdown("""
    <style>
        div[data-testid="stMetric"] {
            background-color: rgba(28, 31, 38, 0.75);
            border: 1px solid rgba(255, 255, 255, 0.08);
            padding: 16px 20px;
            border-radius: 10px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
        }

        div[data-testid="stMetricLabel"] {
            font-size: 0.85rem;
            color: #9ca3af;
            font-weight: 500;
        }

        div[data-testid="stMetricValue"] {
            font-size: 1.55rem;
            font-weight: 700;
        }

        .block-container {
            padding-top: 2rem;
            padding-bottom: 3rem;
        }

        /* Style des conteneurs avec bordure (st.container(border=True)) */
        [data-testid="stVerticalBlockBorderWrapper"] {
            background-color: #1e293b;
            border: 1px solid rgba(56, 189, 248, 0.35) !important;
            border-radius: 12px !important;
            padding: 14px 16px !important;
        }

        .greek-card {
            background-color: rgba(28, 31, 38, 0.75);
            border: 1px solid rgba(255, 255, 255, 0.08);
            padding: 16px 20px;
            border-radius: 10px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
            height: 100%;
            min-height: 165px;
            display: flex;
            flex-direction: column;
            justify-content: space-between;
        }

        .greek-label {
            font-size: 0.85rem;
            color: #9ca3af;
            font-weight: 500;
            margin-bottom: 4px;
        }

        .greek-value {
            font-size: 1.55rem;
            font-weight: 700;
            color: #f8fafc;
            margin-bottom: 10px;
        }

        .greek-desc {
            font-size: 0.85rem;
            color: #cbd5e1;
            line-height: 1.4;
            white-space: normal;
        }
    </style>
""", unsafe_allow_html=True)

st.title("Black-Scholes Pricer")
with st.sidebar:
    st.title("Input Parameter")
    model = st.selectbox(label="Model", options=['European'])
    option_type = st.selectbox(label="Option Type", options=["Call", "Put"])
    K = st.slider(label="Strike (K)", min_value=1, max_value=1000, value=100, step=10, format="%.2f USD")
    r = st.slider(label="Risk Free (r)", min_value=0.0, max_value=20.0, value=3.0, step=0.25, format="%.2f %%")/100
    T = st.slider(label="Time to maturity (T)", min_value=0.01, max_value=2.0, value=0.5, step=0.01, format="%.2f year")
    sigma = st.slider(label="Volatility", min_value=1.0, max_value=100.0, value=15.0, step=1.0, format="%.2f %%")/100
    S = st.number_input(label="Spot Price (S)", min_value=1, max_value=5000, value=100, step=10)

st.write("Option Premium & Strategy Overview")
if option_type == "Call":
    premium = cpp_bridge.call_price(S, K, r, sigma, T)
else:
    premium = cpp_bridge.put_price(S, K, r, sigma, T)

col1, col2 = st.columns(2)
with col1:
    st.metric("Price Premium", f"{premium:.2f} USD")
with col2:
    if option_type == "Call":
        if S/K > 1:
            color_mode = "green"
            delta_str="In the money"
            delta_arrow="up"
        elif S/K < 1:
            color_mode = "red"
            delta_str="Out the money"
            delta_arrow="down"
        else:
            color_mode = "grey"
            delta_str="At the money"
            delta_arrow="off"
    else:
        if S/K > 1:
            color_mode = "red"
            delta_str="Out the money"
            delta_arrow="down"
        elif S/K < 1:
            color_mode = "green"
            delta_str="In the money"
            delta_arrow="up"
        else:
            color_mode = "grey"
            delta_str="At the money"
            delta_arrow="off"
    st.metric(
    "Moneyness (S / K)",
    f"{(S/K):.3f}",
    delta=delta_str,
    delta_color=color_mode,
    delta_arrow=delta_arrow)

if option_type == "Call":
    title = "Hedging Schema : Covered Call Strategy"
    x_max = max(K * 2, S * 1.2)
    px = [0, K, x_max]
    py = [premium, K + premium, K + premium]
    mx = [S]
    my = [min(S, K) + premium]
else:
    title = "Hedging Schema : Protective Put Strategy"
    x_max = max(K * 2, S * 1.2)
    px = [0, K, x_max]
    py = [K-premium, K - premium, x_max - premium]
    mx = [S]
    my = [max(S, K) - premium]
fig = go.Figure()
fig.add_trace(go.Scatter(x=px, y=py, mode="lines", name="Payoff"))
fig.add_trace(go.Scatter(x=mx, y=my, mode="markers", marker=dict(size=8, color="white", symbol="circle"), name="Current Spot (S)"))
fig.update_layout(
                title = title,
                paper_bgcolor="rgba(0,0,0,0)", 
                plot_bgcolor="rgba(0,0,0,0)", 
                xaxis_title="Underlying Price at Maturity ($)",
                yaxis_title="Strategy Value ($)")

st.plotly_chart(fig)

st.write("Greeks Analysis & Interpretation")
g1, g2, g3, g4, g5 = st.columns(5)
with g1:
    if option_type == "Call":
        delta = cpp_bridge.delta_call(S, K, r, sigma, T)
    else:
        delta = cpp_bridge.delta_put(S, K, r, sigma, T)
    st.markdown(f"""
        <div class="greek-card">
            <div>
                <div class="greek-label">Delta (Δ)</div>
                <div class="greek-value">{delta:+.4f}</div>
            </div>
            <div class="greek-desc">The option price varies by about {delta:.2f}$ when the underlying moves by +1$.</div>
        </div>
    """, unsafe_allow_html=True)
with g2:
    gamma = cpp_bridge.gamma(S, K, r, sigma, T)
    st.markdown(f"""
        <div class="greek-card">
            <div>
                <div class="greek-label">Gamma (Γ)</div>
                <div class="greek-value">{gamma:+.4f}</div>
            </div>
            <div class="greek-desc">The option delta varies by approximately {gamma:.4f} when the underlying moves +1$.</div>
        </div>
    """, unsafe_allow_html=True)
with g3:
    if option_type == "Call":
        theta = cpp_bridge.theta_call(S, K, r, sigma, T)
    else:
        theta = cpp_bridge.theta_put(S, K, r, sigma, T)
    st.markdown(f"""
        <div class="greek-card">
            <div>
                <div class="greek-label">Theta (Θ)</div>
                <div class="greek-value">{theta:+.4f}</div>
            </div>
            <div class="greek-desc">The option price varies from about {theta:.2f}$ when time advances by one day.</div>
        </div>
    """, unsafe_allow_html=True)
with g4:
    vega = cpp_bridge.vega(S, K, r, sigma, T)
    st.markdown(f"""
        <div class="greek-card">
            <div>
                <div class="greek-label">Vega (v)</div>
                <div class="greek-value">{vega:+.4f}</div>
            </div>
            <div class="greek-desc">The option price varies by about {vega:.2f}$ when the implied volatility moves by +1%.</div>
        </div>
    """, unsafe_allow_html=True)
with g5:
    if option_type == "Call":
        rho = cpp_bridge.rho_call(S, K, r, sigma, T)
    else:
        rho = cpp_bridge.rho_put(S, K, r, sigma, T)
    st.markdown(f"""
        <div class="greek-card">
            <div>
                <div class="greek-label">Rho (ρ)</div>
                <div class="greek-value">{rho:+.4f}</div>
            </div>
            <div class="greek-desc">The option price varies by about {rho:.2f}$ when the risk-free rate moves by +1%.</div>
        </div>
    """, unsafe_allow_html=True)