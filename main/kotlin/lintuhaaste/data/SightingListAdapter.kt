package lintuhaaste.data

import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView
import android.widget.Filter
import android.widget.TextView
import androidx.navigation.NavController
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.mob2022.lintuhaaste.R
import java.util.*
import kotlin.collections.ArrayList

class SightingListAdapter : ListAdapter<Sighting, SightingListAdapter.SightingViewHolder>(SightingsComparator()) {

    private lateinit var onItemClickListener: OnItemClickListener

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): SightingViewHolder {
        return SightingViewHolder.create(parent)
    }

    override fun onBindViewHolder(holder: SightingViewHolder, position: Int) {
        val current = getItem(position)
        holder.bind(current)

        holder.itemView.setOnClickListener (View.OnClickListener {
            onItemClickListener.onItemClick(
                position
            )
        })

    }

    fun setOnItemClickListener(onItemClickListener: OnItemClickListener) {
        this.onItemClickListener = onItemClickListener
    }

    interface OnItemClickListener {
        fun onItemClick(position: Int)
    }


    class SightingViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        private val sightingDateView: TextView = itemView.findViewById(R.id.dateView)
        private val sightingSpeciesView: TextView = itemView.findViewById(R.id.speciesView)

        fun bind( s: Sighting) {
            sightingDateView.text = s.getDate()
            sightingSpeciesView.text = s.getSpecies()
        }

        companion object {
            fun create(parent: ViewGroup): SightingViewHolder {
                val view: View = LayoutInflater.from(parent.context)
                    .inflate(R.layout.recyclerview_item, parent, false)
                return SightingViewHolder(view)
            }
        }
    }

    class SightingsComparator : DiffUtil.ItemCallback<Sighting>() {
        override fun areItemsTheSame(oldItem: Sighting, newItem: Sighting): Boolean {
            return oldItem === newItem
        }

        override fun areContentsTheSame(oldItem: Sighting, newItem: Sighting): Boolean {
            return oldItem.getSpecies() == newItem.getSpecies()
        }
    }
}