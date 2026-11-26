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
    pricing_model = st.selectbox(label="Model", options=['European'])
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

premium_col, moneyness_col = st.columns(2)
with premium_col:
    st.metric("Price Premium", f"{premium:.2f} USD")
with moneyness_col:
    if option_type == "Call":
        if S/K > 1:
            moneyness_color = "green"
            moneyness_label = "In the money"
            moneyness_arrow = "up"
        elif S/K < 1:
            moneyness_color = "red"
            moneyness_label = "Out of the money"
            moneyness_arrow = "down"
        else:
            moneyness_color = "grey"
            moneyness_label = "At the money"
            moneyness_arrow = "off"
    else:
        if S/K > 1:
            moneyness_color = "red"
            moneyness_label = "Out of the money"
            moneyness_arrow = "down"
        elif S/K < 1:
            moneyness_color = "green"
            moneyness_label = "In the money"
            moneyness_arrow = "up"
        else:
            moneyness_color = "grey"
            moneyness_label = "At the money"
            moneyness_arrow = "off"
    st.metric(
    "Moneyness (S / K)",
    f"{(S/K):.3f}",
    delta = moneyness_label,
    delta_color = moneyness_color,
    delta_arrow = moneyness_arrow)

if option_type == "Call":
    chart_title = "Hedging Schema : Covered Call Strategy"
    x_max = max(K * 2, S * 1.2)
    payoff_x = [0, K, x_max]
    payoff_y = [premium, K + premium, K + premium]
    marker_x = [S]
    marker_y = [min(S, K) + premium]
else:
    chart_title = "Hedging Schema : Protective Put Strategy"
    x_max = max(K * 2, S * 1.2)
    payoff_x = [0, K, x_max]
    payoff_y = [K-premium, K - premium, x_max - premium]
    marker_x = [S]
    marker_y = [max(S, K) - premium]
fig = go.Figure()
fig.add_trace(go.Scatter(x=payoff_x, y=payoff_y, mode="lines", name="Payoff"))
fig.add_trace(go.Scatter(x=marker_x, y=marker_y, mode="markers", marker=dict(size=8, color="white", symbol="circle"), name="Current Spot (S)"))
fig.update_layout(
                title = chart_title,
                paper_bgcolor="rgba(0,0,0,0)", 
                plot_bgcolor="rgba(0,0,0,0)", 
                xaxis_title="Underlying Price at Maturity ($)",
                yaxis_title="Strategy Value ($)")

st.plotly_chart(fig)

st.write("Greeks Analysis & Interpretation")
delta_col, gamma_col, theta_col, vega_col, rho_col = st.columns(5)
with delta_col:
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
with gamma_col:
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
with theta_col:
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
            <div class="greek-desc">The option price varies by about {theta:.2f}$ when time advances by one day.</div>
        </div>
    """, unsafe_allow_html=True)
with vega_col:
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
with rho_col:
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